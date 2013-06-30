#ifndef EXT_TAG_HPP
#define EXT_TAG_HPP

#include <plugins/TagPlugin.hpp>

namespace mru
{

class Ext : public TagPlugin {
public:
  PLUGIN_NAME("Ext")
  Ext(void);
  ~Ext(void);

  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const UnicodeString &a_file_path, const UnicodeString &a_area_of_effect);
};

} /* namespace mru */

#endif /* EXT_TAG_HPP */

