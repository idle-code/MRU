#include "metatag.hpp"

namespace mru
{

Metatag::Metatag(const UnicodeString &a_name)
  : m_name(a_name)
{ }

Metatag::Metatag(const self_type &a_other)
{ }

Metatag::~Metatag(void)
{ }

const UnicodeString &
Metatag::name(void) const
{
  return m_name;
}

void
Metatag::reset(void)
{

}

} /* namespace mru */

