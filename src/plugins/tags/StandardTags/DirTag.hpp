#ifndef DIR_TAG_HPP
#define DIR_TAG_HPP

#include <plugins/TagPlugin.hpp>

namespace mru
{

class DirTag : public TagPlugin {
public:
  PLUGIN_NAME("Dir")
  DirTag(void);
  ~DirTag(void);

  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const UnicodeString &a_file_path, const UnicodeString &a_area_of_effect);
};

} /* namespace mru */

#endif /* DIR_TAG_HPP */

