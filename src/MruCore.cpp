#include "MruCore.hpp"
#undef NDEBUG_L
#include <debug_l.h>
#include "MetatagBase.hpp"

#include "plugins/InputPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/UiPlugin.hpp"
#include "MetatagPluginConverter.hpp"

#include "DllModule.hpp"
#include "BsdDllModule.hpp"

#include "Metatag/Parser.hpp"

#include <boost/property_tree/xml_parser.hpp>

namespace mru {

MruCore::MruCore(void)
{
  // create all managers (it is need to be done before any dynamic module could be loaded):
  input_plugin_manager = InputPlugin::DynamicManager::create();
  output_plugin_manager = OutputPlugin::DynamicManager::create();
  ui_plugin_manager = UiPlugin::DynamicManager::create();
  metatag_plugin_manager = MetatagPlugin::DynamicManager::create();
  
  rename_stopped = true;
}

MruCore::~MruCore(void)
{
  FO("MruCore::~MruCore(void)");
  saveConfiguration();

  ui_plugin.reset();
  output_plugin.reset();
  input_plugin.reset();
}

void
MruCore::saveConfiguration(void)
{
  FilePath configuration_file = reg.get<FilePath>("configuration_file", "mru_config.xml");
  MSG("Saving configuration to: " << glue_cast<std::string>(configuration_file));
  try {
    boost::property_tree::write_xml(glue_cast<std::string>(configuration_file), reg, std::locale());
  } catch (boost::property_tree::file_parser_error &fpe) {
    ERR("Couldn't save configuration file '" << fpe.filename() << "': " << fpe.message() << " (at " << fpe.line() << ")");
  }
}

int
MruCore::start(int argc, char **argv)
{
  FO("MruCore::start(void)");

  loadConfiguration(reg.get<std::string>("configuration_file", "mru_config.xml"));
  loadDefaultConfiguration();

  loadAllModulesIn<InputPlugin>(reg.get<std::string>("plugin.input.directory"), input_plugin_manager);
  loadAllModulesIn<OutputPlugin>(reg.get<std::string>("plugin.output.directory"), output_plugin_manager);
  loadAllModulesIn<UiPlugin>(reg.get<std::string>("plugin.ui.directory"), ui_plugin_manager);

  if (!getInputPlugin()) {
    InputPlugin::Pointer input_plugin = input_plugin_manager->createPlugin(reg.get<std::string>("plugin.input"));

    if (!input_plugin)
      throw Exception("No valid input plugin specified");
    setInputPlugin(input_plugin);
  }

  if (!getOutputPlugin()) {
    OutputPlugin::Pointer output_plugin = output_plugin_manager->createPlugin(reg.get<std::string>("plugin.output"));

    if (!output_plugin)
      throw Exception("No valid output plugin specified");
    setOutputPlugin(output_plugin);
  }

  if (!getUiPlugin()) {
    UiPlugin::Pointer ui_plugin = ui_plugin_manager->createPlugin(reg.get<std::string>("plugin.ui"));

    if (!ui_plugin)
      throw Exception("No valid UI plugin specified");
    setUiPlugin(ui_plugin);
  }

  loadAllModulesIn<MetatagPlugin>(reg.get<std::string>("plugin.tags.directory"), metatag_plugin_manager);

  MetatagPlugin::DynamicManager::FactoryMap::const_iterator i = metatag_plugin_manager->getFactoryMap().begin();
  MetatagPlugin::DynamicManager::FactoryMap::const_iterator i_end = metatag_plugin_manager->getFactoryMap().end();
  for(; i != i_end; ++i) {
    factory_map.insert(std::make_pair(glue_cast<UnicodeString>((*i).first), MetatagPluginToMetatagFactoryConverter::create((*i).second)));
  }

  setSortExpression(glue_cast<UnicodeString>(reg.get<std::string>("run.sort.expression")));
  setMetatagExpression(glue_cast<UnicodeString>(reg.get<std::string>("run.metatag.expression")));

  return getUiPlugin()->start(argc, argv);
}

template<typename PluginType>
void
MruCore::loadAllModulesIn(const FilePath &directory, typename PluginType::DynamicManager::Pointer plugin_manager)
{
  std::list<FilePath> file_list = listFilesInDirectory(directory);

  std::list<FilePath>::const_iterator file_iter = file_list.begin();
  std::list<FilePath>::const_iterator end = file_list.end();
  for(; file_iter != end; ++file_iter) {
    try {
      MSG("Loading " << *file_iter);
      plugin_manager->loadModule(*file_iter);
    } catch (DllModule::Exception &e) {
      WARN(e.getMessage());
    } catch (MruException &e) {
      WARN(e.getMessage());
    }
  }
}

std::list<FilePath>
MruCore::listFilesInDirectory(const FilePath &directory)
{
  std::list<FilePath> file_list;

  if (bfs::exists(directory) && bfs::is_directory(directory)) {
    bfs::directory_iterator end_iter;
    for (bfs::directory_iterator iter(directory); iter != end_iter; ++iter) {
      if (bfs::is_regular_file(iter->status())) {
        file_list.push_back(*iter);
      }
    }
  }

  return file_list;
}

void
MruCore::loadConfiguration(const FilePath &configuration_file)
{
  FO("MruCore::loadConfiguration(void)");
  MSG("Reading configuration from: " << configuration_file);
  try {
    boost::property_tree::read_xml(glue_cast<std::string>(configuration_file), reg, boost::property_tree::xml_parser::trim_whitespace);
    reg.put("configuration_file", configuration_file.generic_string());
  } catch (boost::property_tree::file_parser_error &fpe) { //FIXME: catch (and ignore) proper exception
    WARN("Couldn't read configuration from: " << fpe.filename() << ": " << fpe.message() << " (at " << fpe.line() << ")");
  }
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
  if (ui_plugin)
    ui_plugin->Init(this);
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
  if (output_plugin)
    output_plugin->Init(this);
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
  if (input_plugin)
    input_plugin->Init(this);
}

std::list<std::string>
MruCore::getAvailableMetatags(void)
{
  MetatagPlugin::DynamicManager::FactoryList metatag_factory_list = metatag_plugin_manager->getFactoryList();
  std::list<std::string> result_list;
  MetatagPlugin::DynamicManager::FactoryList::iterator i = metatag_factory_list.begin();
  for(; i != metatag_factory_list.end(); ++i)
    result_list.push_back((*i)->getId());
  return result_list;
}

boost::property_tree::ptree &
MruCore::getConfigTree(void)
{
  return reg;
}

void
MruCore::resetState(void)
{
  if (metatag_expression)
    metatag_expression->reset();
  if (sorting_expression)
    sorting_expression->reset();
}

void
MruCore::startRename(void)
{
  FO("MruCore::startRename(void)");
  if (!rename_stopped) {
    WARN("Renamer thread already running");
    return;
  }
  rename_stopped = false;
  if (0 < pthread_create(&renamer_thread, NULL, &MruCore::renamer_main, (void*)this)) {
    ERR("Cannot create renamer thread");
  }
}

void *
MruCore::renamer_main(void *core_ptr)
{
  FO("MruCore::renamer_main(void *core_ptr)");
  assert(core_ptr);
  MruCore *core = (MruCore*)core_ptr;

  FilePath new_path, old_path, previous_directory;

  FileIterator::Pointer dir_iter = core->getDirectoryIterator();
  core->SignalRenameStarted();
  for (; !core->rename_stopped && !dir_iter->atEnd(); dir_iter->next()) {
    try {
      old_path = dir_iter->getCurrent();
      if (core->reg.get<bool>("run.reset_on_directory_change") &&
          previous_directory != old_path.parent_path())
      {
        core->resetState();
        previous_directory = old_path.parent_path();
      }
      new_path = core->generateNewFilepath(dir_iter);
      core->output_plugin->move(old_path, new_path);
      core->SignalFilenameChange(old_path, new_path);
      usleep(10000);
    } catch (MruException &e) {
      ERR("Mru exception: " << e.getMessage());
      core->SignalRenameError(e);
    } catch (std::exception &e) {
      ERR("Other exception" << e.what());
    }
  }
  core->rename_stopped = true;
  core->SignalRenameStopped();
  
  pthread_exit(NULL);
}

void
MruCore::stopRename(void)
{
  FO("MruCore::stopRename(void)");
  if (rename_stopped) {
    WARN("Renamer thread already stopped");
    return; 
  }
  rename_stopped = true;
  pthread_join(renamer_thread, NULL);
}

/* ------------------------------------------------------------------------- */

MruCore::RegexFilterPredicate::Pointer
MruCore::RegexFilterPredicate::create(const UnicodeString &glob_expression)
{
  return boost::make_shared<RegexFilterPredicate>(glob_expression);
}

MruCore::RegexFilterPredicate::RegexFilterPredicate(const UnicodeString &glob_expression)
  : matcher_status(U_ZERO_ERROR), matcher(glob_expression, 0, matcher_status)
{
  if(U_FAILURE(matcher_status)) {
    VAL(glob_expression);
    throw MruException(u_errorName(matcher_status));
  }
}

bool
MruCore::RegexFilterPredicate::operator()(const FilePath &path)
{
  matcher.reset(glue_cast<UnicodeString>(path));

  bool result = matcher.matches(matcher_status);
  if(U_FAILURE(matcher_status)) {
    VAL(path);
    throw MruException(u_errorName(matcher_status));
  }
  if (result)
    return true;

  matcher.reset(glue_cast<UnicodeString>(path.filename()));
  result = matcher.matches(matcher_status);
  if(U_FAILURE(matcher_status)) {
    VAL(path);
    throw MruException(u_errorName(matcher_status));
  }
  return result;
}

/* ------------------------------------------------------------------------- */

FileIterator::Pointer
MruCore::getDirectoryIterator(void)
{
  assert(input_plugin);
  resetState();
  try {
    input_plugin->includeFiles(reg.get<bool>("run.include.files"));
    input_plugin->includeDirectories(reg.get<bool>("run.include.directories"));
    input_plugin->searchRecursively(reg.get<bool>("run.search.recursively"));
    FileIterator::Pointer file_iterator = input_plugin->getFileIterator(getDirectory());

    if (file_filter_predicate)
      file_iterator = FilteringFileIterator::wrap(file_iterator, file_filter_predicate);

    if (sorting_expression)
      file_iterator = SortingFileIterator::wrap(file_iterator, sort_comparator);

    return file_iterator;
  } catch(InputPlugin::Exception &ie) {
    ERR("Couldn't get directory iterator for: " << getDirectory() << " - " << ie.getMessage());
    return FileIterator::Pointer();
  }
}

FilePath
MruCore::generateNewFilepath(const FileIterator::Pointer file_iterator)
{
  assert(file_iterator && "file_iterator == NULL");
  assert(metatag_expression && "Metatag expression not specified");
  if(reg.get<bool>("run.work_on.directories"))
    return getDirectory() / glue_cast<FilePath>(metatag_expression->evaluate(file_iterator->getCurrent()));
  else
    return file_iterator->getCurrent().parent_path() / glue_cast<FilePath>(metatag_expression->evaluate(file_iterator->getCurrent()));
}

/* ------------------------------------------------------------------------- */

void
MruCore::setDirectory(const FilePath &directory)
{
  reg.put("run.directory", directory.generic_string());
  SignalDirectoryChanged(directory);
}

const FilePath
MruCore::getDirectory(void) const
{
  return reg.get<FilePath>("run.directory");
}

/* ------------------------------------------------------------------------- */

void
MruCore::setFileFilter(const UnicodeString &filter_expression)
{
  file_filter_glob = filter_expression;
  if (filter_expression.isEmpty())
    file_filter_predicate.reset();
  else
    file_filter_predicate = RegexFilterPredicate::create(filter_expression);
  SignalFileFilterChanged(file_filter_glob);
}

const UnicodeString
MruCore::getFileFilter(void)
{
  return file_filter_glob;
}
/* ------------------------------------------------------------------------- */

MruCore::MetatagExpressionComparator::Pointer
MruCore::MetatagExpressionComparator::create(Metatag::Expression::Pointer expression, bool ascending)
{
  return boost::make_shared<MetatagExpressionComparator>(expression, ascending);
}

MruCore::MetatagExpressionComparator::MetatagExpressionComparator(Metatag::Expression::Pointer expression, bool ascending)
  : expression(expression), ascending(ascending)
{
  assert(expression);
}

int
MruCore::MetatagExpressionComparator::operator()(const FilePath &first, const FilePath &second)
{
  UnicodeString first_hash = expression->evaluate(first);
  UnicodeString second_hash = expression->evaluate(second);

  if (first_hash == second_hash)
    return 0;
  if (ascending)
    return first_hash < second_hash ? 1 : -1;
  else
    return first_hash > second_hash ? 1 : -1;
}


/* ------------------------------------------------------------------------- */

void
MruCore::setSortExpression(const UnicodeString &expression)
{
  setSortExpression(Metatag::Expression::parse(expression));
}

void
MruCore::setSortExpression(Metatag::Expression::Pointer expression)
{
  assert(expression);
  VAL(expression->text());
  expression->bindFactoryMap(factory_map, this);
  sorting_expression = expression;
  sort_comparator = MetatagExpressionComparator::create(sorting_expression, (reg.get<std::string>("run.sort.direction") == "ascending"));
  SignalSortExpressionChanged(getSortExpression());
}

Metatag::Expression::Pointer
MruCore::getSortExpression(void)
{
  assert(sorting_expression);
  return sorting_expression;
}

/* ------------------------------------------------------------------------- */

void
MruCore::setMetatagExpression(const UnicodeString &expression)
{
  setMetatagExpression(Metatag::Expression::parse(expression));
}

void
MruCore::setMetatagExpression(Metatag::Expression::Pointer expression)
{
  assert(expression);
  VAL(expression->text());
  expression->bindFactoryMap(factory_map, this);
  metatag_expression = expression;
  SignalMetatagExpressionChanged(getMetatagExpression());
}

Metatag::Expression::Pointer
MruCore::getMetatagExpression(void)
{
  assert(metatag_expression);
  return metatag_expression;
}


} /* namespace mru */

