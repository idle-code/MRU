#ifndef FORMAT_METATAG_HPP
#define FORMAT_METATAG_HPP
#undef NDEBUG_L
#include <debug_l/debug_l.h>
#include <boost/lexical_cast.hpp>
#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class FormatMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(FormatMetatag, MetatagPlugin, "Format");
  FormatMetatag(void);

  void initialize(MruCore *core, const UnicodeString &arguments);
  UnicodeString execute(const FilePath &file_path, const UnicodeString &area_of_effect);
private:
  enum {
    undefined,
    none,
    kilo,
    kilobytes,
    mega,
    megabytes,
  } postfix;

  enum {
    decimal,
    octal,
    hexadecimal,
    size
  } type;

  int prefix_size;
  UnicodeString prefix_fill;
};

} /* namespace mru */

#endif /* FORMAT_METATAG_HPP */

