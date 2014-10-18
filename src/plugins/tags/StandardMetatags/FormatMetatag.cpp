#include "FormatMetatag.hpp"
#include <unicode/regex.h>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

namespace mru
{

FormatMetatag::FormatMetatag(void)
  : postfix(undefined), type(decimal), prefix_size(0), prefix_fill(UChar('0'))
{ }

static const UnicodeString prefix_size_prefix = glue_cast<UnicodeString>("prefix_size=");
static const UnicodeString prefix_fill_prefix = glue_cast<UnicodeString>("prefix_fill=");
static const UnicodeString postfix_prefix = glue_cast<UnicodeString>("postfix=");
static const UnicodeString type_prefix = glue_cast<UnicodeString>("type=");

void
FormatMetatag::initialize(MruCore *core, const UnicodeString &arguments)
{
  UErrorCode status = U_ZERO_ERROR;
  icu::RegexMatcher regex("\\ *,\\ *", 0, status);
  UnicodeString params[4];
  int param_count = regex.split(arguments, params, 4, status);
  if(status != U_ZERO_ERROR) {
    ERR("Error status from regex.split: " << status);
    throw MetatagBase::Exception(glue_cast<UnicodeString>("ICU Regex split error code: ") + glue_cast<UnicodeString>((int) status));
  }
  
  //VAL(param_count);
  for(int i = 0; i < param_count; ++i) {
    params[i] = params[i].trim();
    if(params[i].startsWith(prefix_size_prefix)) {
      try {
        prefix_size = boost::lexical_cast<int>(glue_cast<std::string>(params[i].tempSubString(prefix_size_prefix.length())));
      } catch (boost::bad_lexical_cast) { }
    } else if(params[i].startsWith(prefix_fill_prefix)) {
      prefix_fill = params[i].tempSubString(prefix_fill_prefix.length());
    } else if(params[i].startsWith(postfix_prefix)) {
      UnicodeString postfix_type = params[i].tempSubString(postfix_prefix.length());
      postfix_type = postfix_type.toLower();
      if (postfix_type == "k")
        postfix = kilo;
      else if (postfix_type == "kb")
        postfix = kilobytes;
      else if (postfix_type == "m")
        postfix = mega;
      else if (postfix_type == "mb")
        postfix = megabytes;
      else
        throw MetatagBase::Exception(glue_cast<UnicodeString>("Unknown postfix type: ") + postfix_type);
    } else {
      UnicodeString str_type = params[i];
      if(params[i].startsWith(type_prefix))
        str_type = params[i].tempSubString(type_prefix.length());
      str_type = str_type.toLower();
      if (str_type.startsWith("dec"))
        type = decimal;
      else if (str_type.startsWith("oct"))
        type = octal;
      else if (str_type.startsWith("hex"))
        type = hexadecimal;
      else if (str_type == "size")
        type = size;
      else
        throw MetatagBase::Exception(glue_cast<UnicodeString>("Unknown format type: ") + str_type);
    }
  }
}

UnicodeString FormatMetatag::execute(const FilePath &, const UnicodeString &area_of_effect)
{
  double number = 0;
  UnicodeString str_number = area_of_effect;
  str_number = str_number.trim();

  try {
    number = boost::lexical_cast<double>(glue_cast<std::string>(str_number));
  } catch (boost::bad_lexical_cast) {
    return UnicodeString(); //FIXME
    throw MetatagPlugin::Exception(glue_cast<UnicodeString>("Cannot parse '") + area_of_effect + "' as number");
  }

  switch (postfix) {
    case undefined:
      break;
    case none:
      break;
    case kilo:
      number /= 1000;
      break;
    case kilobytes:
      number /= 1024;
      break;
    case mega:
      number /= 1000 * 1000;
      break;
    case megabytes:
      number /= 1024 * 1024;
      break;
  }

  switch (type) {
    case decimal:
      str_number = glue_cast<UnicodeString>(str(boost::format("%d") % (long)number));
      break;
    case octal:
      str_number = glue_cast<UnicodeString>(str(boost::format("%o") % (long)number));
      break;
    case hexadecimal:
      str_number = glue_cast<UnicodeString>(str(boost::format("%x") % (long)number));
      break;
    case size:
      break;
  }

  if (prefix_size > 0 && prefix_fill.length() > 0) {
    while (str_number.length() < prefix_size)
      str_number = prefix_fill + str_number;
  }

  return str_number; 
}

} /* namespace mru */

