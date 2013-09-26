#ifndef COUNT_TAG_HPP
#define COUNT_TAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class CountMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(CountMetatag, MetatagPlugin, "Count");
  CountMetatag(void);

  void reset(void);
  void initialize(MruCore *core, const UnicodeString &a_arguments);
  UnicodeString execute(const FilePath &a_file_path, const UnicodeString &a_area_of_effect);
private:
  int UnicodeStringToInt(const UnicodeString &a_value);
  int m_counter;
  int m_start;
  int m_step;
};

} /* namespace mru */

#endif /* COUNT_TAG_HPP */

