#include "TextCaseTag.hpp"

namespace mru
{

TextCaseTag::TextCaseTag(void)
  : TagPlugin(static_implementation_name())
{ }

TextCaseTag::~TextCaseTag(void)
{ }

void
TextCaseTag::initialize(const UnicodeString &a_arguments)
{
  if(a_arguments == glue_cast<UnicodeString>("upper"))
    m_action = to_upper;
  else if(a_arguments == glue_cast<UnicodeString>("lower"))
    m_action = to_lower;
  else if(a_arguments == glue_cast<UnicodeString>("title"))
    m_action = to_title;
  else
    throw MetatagException(name(), glue_cast<UnicodeString>("Unsupported argument: ") + a_arguments);
}

UnicodeString
TextCaseTag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)
{
  UnicodeString area_of_effect = a_area_of_effect;
  switch(m_action) {
    case to_upper:
      return area_of_effect.toUpper();  
    case to_lower:
      return area_of_effect.toLower();  
    case to_title:
      return area_of_effect.toTitle(NULL);
    default:
      throw MetatagException(name(), glue_cast<UnicodeString>("Unsupported action: ") + m_action);
  }
}

} /* namespace mru */
