#include "MruCore.hpp"
#include <unistd.h> // for getcwd
#include <sys/param.h> // for MAXPATHLEN

namespace mru {

void
MruCore::loadDefaultConfiguration(void)
{
  reg.put("configuration_file", "./mru_config.xml");

  //reg.put("plugin.directory", "/usr/local/lib/mru");
  reg.put("plugin.directory", "plugins");
  FilePath plugins_directory_root = reg.get<std::string>("plugin.directory");

  reg.put("plugin.input", "BoostInput");
  reg.put<std::string>("plugin.input.directory", (plugins_directory_root / "input").generic_string());

  reg.put("plugin.output", "BoostOutput");
  reg.put<std::string>("plugin.output.directory", (plugins_directory_root / "output").generic_string());

  reg.put("plugin.ui", "wxWidgetsUi");
  reg.put<std::string>("plugin.ui.directory", (plugins_directory_root / "ui").generic_string());

  char *current_directory = new char[MAXPATHLEN];
  if (NULL != getcwd(current_directory, MAXPATHLEN))
    reg.put<std::string>("run.directory", current_directory);
  else
    throw MruCore::Exception("Couldn't find current directory");
}


} /* namespace mru  */

