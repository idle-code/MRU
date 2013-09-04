#ifndef MRU_EXCEPTION_HPP
#define MRU_EXCEPTION_HPP

#include "types.hpp"
#include "glue.hpp"
#include <stdexcept>
#include <stack>

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
  std::stack<UnicodeString> module_path;
};

#define MODULE_EXCEPTION(Module, ParentException) \
class Exception : public ParentException { \
public: \
  Exception(const UnicodeString &message) throw() \
    : ParentException(message) { module_path.push(#Module); } \
  virtual ~Exception(void) throw() { } \
}

} /* namespace mru */

#endif /* MRU_EXCEPTION_HPP */

