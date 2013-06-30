#ifndef METATAG_HPP
#define METATAG_HPP

#include "types.hpp"
#include "FileIterator.hpp"

namespace mru
{

class Metatag {
public:
  typedef Metatag self_type;
public:
  Metatag(const UnicodeString &a_name);
  const UnicodeString& name(void) const;
  virtual ~Metatag(void);

  virtual void reset(void);
  virtual void initialize(const UnicodeString &a_arguments) = 0;
  virtual UnicodeString execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect) = 0;
protected:
  Metatag(const self_type &a_other); // = delete;
  UnicodeString m_name;
};

} /* namespace mru */

#endif /* METATAG_HPP */

