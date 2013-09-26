#include "MruCore.hpp"
#include <unistd.h> // for getcwd
#include <sys/param.h> // for MAXPATHLEN

namespace mru {

void
putOptional(boost::property_tree::ptree &reg, std::string path, std::string value)
{
  //if (reg.count(path) == 0)
  //if (reg.get_optional<std::string>(path))
  //  reg.put<std::string>(path, value);
  try {
    reg.get<std::string>(path);
  } catch (boost::property_tree::ptree_bad_path &) {
    reg.put<std::string>(path, value);
  }
}

void
putOptional(boost::property_tree::ptree &reg, std::string path, const char *value)
{
  putOptional(reg, path, std::string(value));
}

void
putOptional(boost::property_tree::ptree &reg, std::string path, bool value)
{
  //if (reg.count(path) == 0)
  try {
    reg.get<bool>(path);
  } catch (boost::property_tree::ptree_bad_path &) {
    reg.put<bool>(path, value);
  }
}

void
MruCore::loadDefaultConfiguration(void)
{
  //putOptional(reg, "configuration_file", "./mru_config.xml");
  putOptional(reg, "run.metatag.expression", "%Name()%Ext()");

  //reg.put("plugin.directory", "/usr/local/lib/mru");
  putOptional(reg, "plugin.directory", "plugins");
  FilePath plugins_directory_root = reg.get<std::string>("plugin.directory");

  putOptional(reg, "plugin.input", "mru::BoostInput");
  putOptional(reg, "plugin.input.directory", (plugins_directory_root / "input").generic_string());

  putOptional(reg, "plugin.output", "mru::BoostOutput");
  putOptional(reg, "plugin.output.directory", (plugins_directory_root / "output").generic_string());

  putOptional(reg, "plugin.ui", "mru::wxWidgetsUi");
  putOptional(reg, "plugin.ui.directory", (plugins_directory_root / "ui").generic_string());

  putOptional(reg, "plugin.tags.directory", (plugins_directory_root / "tags").generic_string());

  char *current_directory = new char[MAXPATHLEN];
  if (NULL != getcwd(current_directory, MAXPATHLEN))
    putOptional(reg, "run.directory", current_directory);
  else {
    delete [] current_directory;
    throw MruCore::Exception("Couldn't find current directory");
  }
  delete [] current_directory;

  putOptional(reg, "run.work_on.directories", false);
  putOptional(reg, "run.work_on.files", true);
  putOptional(reg, "run.include.directories", false);
  putOptional(reg, "run.include.files", true);
  putOptional(reg, "run.search.recursively", true);
  putOptional(reg, "run.reset_on_directory_change", true);

}


} /* namespace mru  */

