#ifndef SIZE_METATAG_HPP
#define SIZE_METATAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class SizeMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(SizeMetatag, MetatagPlugin, "Size");
  SizeMetatag(void);

  void initialize(MruCore *core, const UnicodeString &arguments);
  UnicodeString execute(const FilePath &file_path, const UnicodeString &area_of_effect);
};

} /* namespace mru */

#endif /* SIZE_METATAG_HPP */

