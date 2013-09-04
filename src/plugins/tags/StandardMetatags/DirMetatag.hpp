#ifndef DIR_TAG_HPP
#define DIR_TAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class DirMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(DirMetatag, MetatagPlugin, "Dir");
  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const FileIterator::Pointer a_file_path, const UnicodeString &a_area_of_effect);
};

} /* namespace mru */

#endif /* DIR_TAG_HPP */

