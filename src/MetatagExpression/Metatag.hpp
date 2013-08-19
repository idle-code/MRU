#ifndef METATAG_HPP
#define METATAG_HPP

#include "types.hpp"
#include "FileIterator.hpp"

namespace mru
{

class Metatag {
public:
  typedef boost::shared_ptr<Metatag> Pointer;
public:
  Metatag(const UnicodeString &name);
  const UnicodeString& getName(void) const;
  virtual ~Metatag(void);

  virtual void reset(void);
  virtual void initialize(const UnicodeString &arguments) = 0;
  virtual UnicodeString execute(const FileIterator &file_path, const UnicodeString &areof_effect) = 0;
protected:
  UnicodeString name;
};

class MetatagException : public std::runtime_error {
public:
  MetatagException(const UnicodeString &tag_name, const UnicodeString &message);
  ~MetatagException(void) throw();
  const char* what(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  UnicodeString tag_name;
  UnicodeString message;
};

} /* namespace mru */

#endif /* METATAG_HPP */

