#include "Metatag.hpp"
#include "glue.hpp"

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

/* ------------------------------------------------------------------------- */


MetatagException::MetatagException(const UnicodeString &a_tag_name, const UnicodeString &a_message)
  : std::runtime_error(glue_cast<std::string>(a_message).c_str()),
    m_tag_name(a_tag_name), m_message(a_message)
{ }

MetatagException::~MetatagException(void) throw()
{ }

const char *
MetatagException::what(void) const throw()
{
  return (std::string("From tag ") + glue_cast<std::string>(m_tag_name) + ": " + glue_cast<std::string>(m_message)).c_str();
}

const UnicodeString &
MetatagException::message(void) const throw()
{
  return m_message;
}

} /* namespace mru */

