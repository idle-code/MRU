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
  Metatag(const UnicodeString &a_name);
  const UnicodeString& name(void) const;
  virtual ~Metatag(void);

  virtual void reset(void);
  virtual void initialize(const UnicodeString &a_arguments) = 0;
  virtual UnicodeString execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect) = 0;
protected:
  UnicodeString m_name;
};

class MetatagException : public std::runtime_error {
public:
  MetatagException(const UnicodeString &a_tag_name, const UnicodeString &a_message);
  ~MetatagException(void) throw();
  const char* what(void) const throw();
  const UnicodeString& message(void) const throw();
private:
  UnicodeString m_tag_name;
  UnicodeString m_message;
};

} /* namespace mru */

#endif /* METATAG_HPP */

