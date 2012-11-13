#ifndef DYNAMIC_MODULE_BSD_HPP
#define DYNAMIC_MODULE_BSD_HPP

#include <dynamic_module.hpp>

namespace mru
{

class dynamic_module_bsd : public dynamic_module {
public:
  dynamic_module_bsd(const name_type &a_file_path);
  ~dynamic_module_bsd(void);

  bool is_loaded(void) const;
  void* get_symbol(const name_type &a_symbol);
  const name_type filename_prefix(void) const;
  const name_type filename_postfix(void) const;
private:
  void *m_module_handle;
  static const name_type m_prefix;
  static const name_type m_postfix;
};

} /* namespace mru */

#endif /* DYNAMIC_MODULE_BSD_HPP */

