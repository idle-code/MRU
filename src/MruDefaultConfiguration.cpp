#include "MruCore.hpp"
#include <unistd.h> // for getcwd
#include <sys/param.h> // for MAXPATHLEN

namespace mru {

void
MruCore::loadDefaultConfiguration(void)
{
  reg.put("configuration_file", FilePath("~/.mru_config.json"));

  reg.put("plugin.ui", "wxWidgetsUi");
  reg.put("plugin.output", "BoostOutputPlugin");
  reg.put("plugin.input", "BoosInputPlugin");

  FilePath plugins_directory_root = "/usr/local/lib/mru";
  reg.put("plugin.ui.directory", plugins_directory_root / "ui");
  reg.put("plugin.output.directory", plugins_directory_root / "output");
  reg.put("plugin.input.directory", plugins_directory_root / "input");

  char *current_directory = new char[MAXPATHLEN];
  if (NULL != getcwd(current_directory, MAXPATHLEN))
    reg.put("run.directory", FilePath(current_directory));
  else
    throw MruCore::Exception("Couldnt find current directory");
}


} /* namespace mru  */

