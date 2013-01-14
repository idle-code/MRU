#ifndef DYNAMIC_MODULE_BSD_HPP
#define DYNAMIC_MODULE_BSD_HPP

#include <dynamic_module.hpp>

namespace mru
{

class dynamic_module_bsd : public dynamic_module {
public:
  dynamic_module_bsd(void);
  ~dynamic_module_bsd(void);
  bool load(const filepath_type &a_file_path);
  bool unload(void);
  bool is_loaded(void) const;
  void* get_symbol(const name_type &a_symbol);

  const filepath_type&        filepath(void) const;
  const filepath_type filename_prefix(void) const;
  const filepath_type filename_postfix(void) const;
protected:
  void *m_module_handle;
  static const filepath_type::string_type m_prefix;
  static const filepath_type::string_type m_postfix;
};

} /* namespace mru */

#endif /* DYNAMIC_MODULE_BSD_HPP */

