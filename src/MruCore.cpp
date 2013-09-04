#define PLUGIN_HOST
#include "MruCore.hpp"
#undef NDEBUG_L
#include <debug_l.h>
#include "MetatagBase.hpp"

#include <boost/property_tree/json_parser.hpp>

namespace mru {


MruCore::MruCore(void)
{
  // create all managers (it is need to be done before any dynamic module could be loaded):
  metatag_plugin_manager = MetatagPluginManager::create();

  loadDefaultConfiguration();
}

void
MruCore::loadConfiguration(const FilePath &configuration_file)
{
  FO("MruCore::loadConfiguration(void)");
  reg.put("configuration_file", configuration_file);
  MSG("Reading configuration from: " << configuration_file);
  try {
    boost::property_tree::read_json(glue_cast<std::string>(reg.get<FilePath>("configuration_file")), reg);
  } catch(boost::property_tree::file_parser_error &fpe) { //FIXME: catch (and ignore) proper exception
    WARN("Couldn't read configuration from: " << fpe.filename() << " - " << fpe.message() << " (at " << fpe.line() << ")");
  }
}

MruCore::~MruCore(void)
{
  FO("MruCore::~MruCore(void)");
  saveConfiguration();
}

void
MruCore::saveConfiguration(void)
{
  FilePath configuration_file = reg.get<FilePath>("config_file", "~/.mru_config.json");
  MSG("Saving configuration to: " << glue_cast<std::string>(configuration_file));
  boost::property_tree::write_json(glue_cast<std::string>(configuration_file), reg);
}

int
MruCore::start(int argc, char **argv)
{
  FO("MruCore::start(void)");

  //if (!getInputPlugin()) {
  //  InputPluginManager::get_instance()->load_module
  //}

  assert(getInputPlugin() != NULL && "No valid input plugin specified");
  assert(getOutputPlugin() != NULL && "No valid output plugin specified");
  assert(getUiPlugin() != NULL && "No valid UI plugin specified");
  return getUiPlugin()->start(argc, argv);
}

UiPlugin::Pointer
MruCore::getUiPlugin(void)
{
  return ui_plugin;
}

void
MruCore::setUiPlugin(UiPlugin::Pointer plugin)
{
  ui_plugin = plugin;
}

OutputPlugin::Pointer
MruCore::getOutputPlugin(void)
{
  return output_plugin;
}

void
MruCore::setOutputPlugin(OutputPlugin::Pointer plugin)
{
  output_plugin = plugin;
}

InputPlugin::Pointer
MruCore::getInputPlugin(void)
{
  return input_plugin;
}

void
MruCore::setInputPlugin(InputPlugin::Pointer plugin)
{
  input_plugin = plugin;
}

/* ------------------------------------------------------------------------- */

void
MruCore::setMetatagExpression(Metatag::Expression::Pointer expression)
{

}

Metatag::Expression::Pointer
MruCore::getMetatagExpression(void)
{
  return Metatag::Expression::Pointer();
}

void
MruCore::resetState(void)
{

}

/* ------------------------------------------------------------------------- */

void
MruCore::startRename(void)
{
}

void
MruCore::stopRename(void)
{
}

/* ------------------------------------------------------------------------- */

FileIterator::Pointer
MruCore::getIterator(void)
{
  assert(input_plugin);
  try {
    return input_plugin->getFileIterator(getDirectory());
  } catch(...) {
    ERR("Couldn't get directory iterator for: " << getDirectory());
    return FileIterator::Pointer();
  }
}

FilePath
MruCore::generateNewFilepath(const FileIterator::Pointer file_iterator)
{
  assert(file_iterator && "file_iterator == NULL");

  return FilePath();
}

/* ------------------------------------------------------------------------- */

void
MruCore::setDirectory(const FilePath &directory)
{
  reg.put("run.directory", directory);
  SignalDirectoryChanged(directory);
}

const FilePath
MruCore::getDirectory(void) const
{
  return reg.get<FilePath>("run.directory");
}

} /* namespace mru */

