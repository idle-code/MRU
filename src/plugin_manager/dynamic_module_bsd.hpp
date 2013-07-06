#ifndef DYNAMIC_MODULE_BSD_HPP
#define DYNAMIC_MODULE_BSD_HPP

#include <dynamic_module.hpp>

namespace mru
{

class dynamic_module_bsd : public dynamic_module {
public:
  dynamic_module_bsd(void);
  ~dynamic_module_bsd(void);
  bool load(const std::string &a_file_path);
  bool unload(void);
  bool is_loaded(void) const;
  void* get_symbol(const std::string &a_symbol);

  const std::string& filepath(void) const;
  const std::string filename_prefix(void) const;
  const std::string filename_postfix(void) const;
protected:
  void *m_module_handle;
  static const std::string m_prefix;
  static const std::string m_postfix;
};

} /* namespace mru */

#endif /* DYNAMIC_MODULE_BSD_HPP */

