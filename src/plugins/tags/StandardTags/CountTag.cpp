#include "CountTag.hpp"
#include <unicode/regex.h>

namespace mru
{

CountTag::CountTag(void)
  : TagPlugin(static_implementation_name()), m_counter(0), m_start(0), m_step(1)
{ }

CountTag::~CountTag(void)
{ }

void
CountTag::reset(void)
{
  FO("CountTag::reset(void)");
  m_counter = m_start;
}

static const UnicodeString start_param_prefix = glue_cast<UnicodeString>("start=");
static const UnicodeString step_param_prefix = glue_cast<UnicodeString>("step=");

int
CountTag::UnicodeStringToInt(const UnicodeString &a_value)
{
  Formattable parse_result;
  UErrorCode status = U_ZERO_ERROR;
  NumberFormat *fmt = NumberFormat::createInstance(status);

  fmt->parse(a_value, parse_result, status);
  if(U_FAILURE(status)) {
    ERR("Error while parsing start parameter");
    throw MetatagException(name(), glue_cast<UnicodeString>("Bad argument parameter: ") + a_value);
  }
  delete fmt;

  return parse_result.getLong();
}

void
CountTag::initialize(const UnicodeString &a_arguments)
{
  FO("CountTag::initialize(const UnicodeString &a_arguments)");

  UErrorCode status = U_ZERO_ERROR;
  icu::RegexMatcher regex("\\ *,\\ *", 0, status);
  UnicodeString params[2];
  int param_count = regex.split(a_arguments, params, 2, status);
  if(status != U_ZERO_ERROR) {
    ERR("Error status from regex.split: " << status);
    throw MetatagException(name(), glue_cast<UnicodeString>("ICU Regex split error code: ") + glue_cast<UnicodeString>((int) status));
  }
  
  for(int i = 0; i < param_count; ++i) {
    params[i] = params[i].trim();
    if(params[i].startsWith(start_param_prefix)) {
      //VAL(glue_cast<std::string>(params[i].tempSubString(start_param_prefix.length())));
      m_start = UnicodeStringToInt(params[i].tempSubString(start_param_prefix.length()));
    } else if(params[i].startsWith(step_param_prefix)) {
      //VAL(glue_cast<std::string>(params[i].tempSubString(step_param_prefix.length())));
      m_step = UnicodeStringToInt(params[i].tempSubString(step_param_prefix.length()));
    } else
      throw MetatagException(name(), glue_cast<UnicodeString>("Unknown argument: ") + params[i]);
  }
  //VAL(m_start);
  //VAL(m_step);
  m_counter = m_start;
}

UnicodeString
CountTag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)
{
  int value = m_counter; 
  m_counter += m_step; 
  return glue_cast<UnicodeString>(value);
}

} /* namespace mru */

