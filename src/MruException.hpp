#ifndef MRU_EXCEPTION_HPP
#define MRU_EXCEPTION_HPP

#include "types.hpp"
#include "glue.hpp"
#include <stdexcept>
#include <list>

namespace mru
{

class MruException : public std::runtime_error {
public:
  MruException(const UnicodeString &message) throw()
    : std::runtime_error(glue_cast<std::string>(message).c_str()), message(message)
  { module_path.push_back("Mru"); }

  virtual ~MruException(void) throw()
  { }

  const UnicodeString getMessage(void) const throw()
  {
    return message;
  }

  const UnicodeString getModulePath(void) const throw()
  {
    UnicodeString merged_module_path;
    for(std::list<UnicodeString>::const_iterator i = module_path.begin(); i != module_path.end(); ++i)
      merged_module_path += "::" + (*i);
    return merged_module_path;
  }
protected:
  UnicodeString message;
  std::list<UnicodeString> module_path;
};

#define MODULE_EXCEPTION(Module, ParentException) \
class Exception : public ParentException { \
public: \
  Exception(const UnicodeString &message) throw() \
    : ParentException(message) { MruException::module_path.push_back(#Module); } \
  virtual ~Exception(void) throw() { } \
}

} /* namespace mru */

#endif /* MRU_EXCEPTION_HPP */

