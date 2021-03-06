#ifndef METATAG_HPP
#define METATAG_HPP

#include "types.hpp"
#include "FileIterator.hpp"

namespace mru {

class MruCore; //forward declaration

namespace Metatag {

template<typename Base>
class AbstractFactory {
public:
  typedef boost::shared_ptr<AbstractFactory> Pointer;
  virtual typename Base::Pointer create(void) {
    return typename Base::Pointer(); //cannot create instance of abstract Base class
  }
};

class MetatagBase {
public:
  typedef boost::shared_ptr<MetatagBase> Pointer;
  typedef AbstractFactory<MetatagBase> Factory;
  class Exception;
  friend class Exception;
public:
  MetatagBase(void);
  virtual ~MetatagBase(void);

  virtual void reset(void);
  virtual void initialize(MruCore *core, const UnicodeString &arguments) = 0;
  virtual UnicodeString execute(const FilePath &file_path, const UnicodeString &area_of_effect) = 0;
};

class MetatagBase::Exception : public std::runtime_error {
public:
  Exception(const UnicodeString &tag_name, const UnicodeString &message);
  Exception(const UnicodeString &message);
  ~Exception(void) throw();
  const char* what(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  UnicodeString tag_name;
  UnicodeString message;
};

} /* namespace Metatag */
} /* namespace mru */

#endif /* METATAG_HPP */

