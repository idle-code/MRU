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

};

} /* namespace mru */

#endif /* STANDARDTAGS_HPP */

