#ifndef MRU_EXCEPTION_HPP
#define MRU_EXCEPTION_HPP

#include "types.hpp"
#include "glue.hpp"
#include <stdexcept>

namespace mru
{

class MruException : public std::runtime_error {
public:
  MruException(const UnicodeString &message) throw()
    : std::runtime_error(glue_cast<std::string>(message).c_str())
  { }

  virtual ~MruException(void) throw()
  { }

  const UnicodeString& getMessage(void) const throw()
  {
    return message;
  }
protected:
  UnicodeString message;
};

} /* namespace mru */

#endif /* MRU_EXCEPTION_HPP */

