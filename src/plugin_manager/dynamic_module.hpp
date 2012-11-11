#ifndef DYNAMIC_MODULE_HPP
#define DYNAMIC_MODULE_HPP

#include <string>

namespace mru
{

class dynamic_module {
public:
  typedef std::string name_type;

  static dynamic_module* load(const name_type &a_file_path);
public:
  dynamic_module(const name_type &a_file_path);
  virtual ~dynamic_module(void);

  virtual void* get_symbol(const name_type &a_symbol) = 0;

  const name_type& filepath(void) const;
  virtual const name_type& filename_prefix(void) const;
  virtual const name_type& filename_postfix(void) const;
protected:
  name_type m_file_path;  
};

} /* namespace mru */

#endif /* DYNAMIC_MODULE_HPP */

