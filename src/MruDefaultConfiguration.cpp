#include "MruCore.hpp"
#include <unistd.h> // for getcwd
#include <sys/param.h> // for MAXPATHLEN

namespace mru {

void
MruCore::loadDefaultConfiguration(void)
{
  reg.put("configuration_file", "./mru_config.xml");

  reg.put<std::string>("run.metatag.expression", "");

  //reg.put("plugin.directory", "/usr/local/lib/mru");
  reg.put("plugin.directory", "plugins");
  FilePath plugins_directory_root = reg.get<std::string>("plugin.directory");

  reg.put("plugin.input", "mru::BoostInput");
  reg.put<std::string>("plugin.input.directory", (plugins_directory_root / "input").generic_string());

  reg.put("plugin.output", "mru::BoostOutput");
  reg.put<std::string>("plugin.output.directory", (plugins_directory_root / "output").generic_string());

  reg.put("plugin.ui", "mru::wxWidgetsUi");
  reg.put<std::string>("plugin.ui.directory", (plugins_directory_root / "ui").generic_string());

  reg.put<std::string>("plugin.tags.directory", (plugins_directory_root / "tags").generic_string());

  char *current_directory = new char[MAXPATHLEN];
  if (NULL != getcwd(current_directory, MAXPATHLEN))
    reg.put<std::string>("run.directory", current_directory);
  else
    throw MruCore::Exception("Couldn't find current directory");

  reg.put("run.work_on.directories", false);
  reg.put("run.work_on.files", true);
  reg.put("run.include.directories", false);
  reg.put("run.include.files", true);
  reg.put("run.search.recursively", true);
  reg.put("run.reset_on_directory_change", true);

}


} /* namespace mru  */

