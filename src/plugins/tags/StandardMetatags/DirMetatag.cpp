#include "DirMetatag.hpp"
#include "make_relative_fix.hpp"
#include "MruCore.hpp"

namespace mru
{

void
DirMetatag::initialize(MruCore *core, const UnicodeString &a_arguments)
{
  this->core = core;
}

UnicodeString
DirMetatag::execute(const FilePath &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(bfs::make_relative(core->getDirectory(), a_file_path.parent_path()));
}

} /* namespace mru */

