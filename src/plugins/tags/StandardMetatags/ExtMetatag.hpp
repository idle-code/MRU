#ifndef EXT_TAG_HPP
#define EXT_TAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class ExtMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(ExtMetatag, MetatagPlugin, "Ext");
  void initialize(MruCore *core, const UnicodeString &a_arguments);
  UnicodeString execute(const FilePath &a_file_path, const UnicodeString &a_area_of_effect);
};

} /* namespace mru */

#endif /* EXT_TAG_HPP */

