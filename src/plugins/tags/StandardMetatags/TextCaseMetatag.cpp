#include "TextCaseMetatag.hpp"

namespace mru
{

void
TextCaseMetatag::initialize(const UnicodeString &a_arguments)
{
  if(a_arguments == glue_cast<UnicodeString>("upper"))
    m_action = to_upper;
  else if(a_arguments == glue_cast<UnicodeString>("lower"))
    m_action = to_lower;
  else if(a_arguments == glue_cast<UnicodeString>("title"))
    m_action = to_title;
  else
    throw MetatagBase::Exception(getName(), glue_cast<UnicodeString>("Unsupported argument: ") + a_arguments);
}

UnicodeString
TextCaseMetatag::execute(const FileIterator::Pointer a_file_path, const UnicodeString &a_area_of_effect)
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
      throw MetatagBase::Exception(getName(), glue_cast<UnicodeString>("Unsupported action: ") + m_action);
  }
}

} /* namespace mru */

