#ifndef STANDARDTAGS_HPP
#define STANDARDTAGS_HPP

#include <plugins/TagPlugin.hpp>

namespace mru
{

class Count : public TagPlugin {
public:
  PLUGIN_NAME("Count")
  Count(void);
  ~Count(void);

  void reset(void);
  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect);
private:
  int m_counter;
};

} /* namespace mru */

#endif /* STANDARDTAGS_HPP */

