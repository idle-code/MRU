#include "StandardTags.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

Count::Count(void)
  : TagPlugin(static_implementation_name()), m_counter(0)
{
  //FO("Count::Count(void)");

}

Count::~Count(void)
{
  //FO("Count::~Count(void)");
}

void
Count::reset(void)
{
  m_counter = 0;
}

void
Count::initialize(const UnicodeString &a_arguments)
{
  //FO("Core::initialize(const UnicodeString &a_arguments)");
  //VAL(glue_cast<std::string>(a_arguments));

}

UnicodeString
Count::execute(const UnicodeString &a_file_path, const UnicodeString &a_area_of_effect)
{
  //FO("Core::execute(const UnicodeString &a_area_of_effect)");
  //VAL(glue_cast<std::string>(a_file_path));
  //VAL(glue_cast<std::string>(a_area_of_effect));
  return glue_cast<UnicodeString>(m_counter++);
}

} /* namespace mru */

#include "ExtTag.hpp"
#include "NameTag.hpp"
#include "DirTag.hpp"

EXPORT_START
  EXPORT_PLUGIN(mru::Count)
  EXPORT_PLUGIN(mru::ExtTag)
  EXPORT_PLUGIN(mru::NameTag)
  EXPORT_PLUGIN(mru::DirTag)
EXPORT_END

