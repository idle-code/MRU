#ifndef METATAG_HPP
#define METATAG_HPP

#include "types.hpp"
#include "FileIterator.hpp"

namespace mru
{

template<typename Base>
class AbstractFactory {
public:
  typedef boost::shared_ptr<AbstractFactory> Pointer;
  virtual typename Base::Pointer create(void) {
    return typename Base::Pointer(); //cannot create instance of abstract Base class
  }
};

class Metatag {
public:
  typedef boost::shared_ptr<Metatag> Pointer;
  typedef AbstractFactory<Metatag> Factory;
  class Exception;
  friend class Exception;
public:
  Metatag(const UnicodeString &name);
  const UnicodeString& getName(void) const;
  virtual ~Metatag(void);

  virtual void reset(void);
  virtual void initialize(const UnicodeString &arguments) = 0;
  virtual UnicodeString execute(const FileIterator::Pointer file_path, const UnicodeString &area_of_effect) = 0;
protected:
  UnicodeString name;
};

class Metatag::Exception : public std::runtime_error {
public:
  Exception(const UnicodeString &tag_name, const UnicodeString &message);
  ~Exception(void) throw();
  const char* what(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  UnicodeString tag_name;
  UnicodeString message;
};

} /* namespace mru */

#endif /* METATAG_HPP */

