#include "MetatagBase.hpp"
#include "glue.hpp"

namespace mru {
namespace Metatag {

MetatagBase::MetatagBase(void)
{ }

MetatagBase::~MetatagBase(void)
{ }

void
MetatagBase::reset(void)
{

}

/* ------------------------------------------------------------------------- */

MetatagBase::Exception::Exception(const UnicodeString &tag_name, const UnicodeString &message)
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    tag_name(tag_name), message(message)
{ }

MetatagBase::Exception::Exception(const UnicodeString &message)
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    message(message)
{ }

MetatagBase::Exception::~Exception(void) throw()
{ }

const char *
MetatagBase::Exception::what(void) const throw()
{
  return (std::string("From tag ") + glue_cast<std::string>(tag_name) + ": " + glue_cast<std::string>(message)).c_str();
}

const UnicodeString &
MetatagBase::Exception::getMessage(void) const throw()
{
  return message;
}

} /* namespace Metatag */
} /* namespace mru */

