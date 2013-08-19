#include "Metatag.hpp"
#include "glue.hpp"

namespace mru
{

Metatag::Metatag(const UnicodeString &name)
  : name(name)
{ }

Metatag::~Metatag(void)
{ }

const UnicodeString &
Metatag::getName(void) const
{
  return name;
}

void
Metatag::reset(void)
{

}

/* ------------------------------------------------------------------------- */

MetatagException::MetatagException(const UnicodeString &tag_name, const UnicodeString &message)
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    tag_name(tag_name), message(message)
{ }

MetatagException::~MetatagException(void) throw()
{ }

const char *
MetatagException::what(void) const throw()
{
  return (std::string("From tag ") + glue_cast<std::string>(tag_name) + ": " + glue_cast<std::string>(message)).c_str();
}

const UnicodeString &
MetatagException::getMessage(void) const throw()
{
  return message;
}

} /* namespace mru */

