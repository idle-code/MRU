#ifndef NAME_TAG_HPP
#define NAME_TAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class NameMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(NameMetatag, MetatagPlugin, "Name");
  void initialize(MruCore *core, const UnicodeString &a_arguments);
  UnicodeString execute(const FilePath &a_file_path, const UnicodeString &a_area_of_effect);
};

} /* namespace mru */

#endif /* NAME_TAG_HPP */

