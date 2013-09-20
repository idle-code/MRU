#include "MruCore.hpp"

#undef NDEBUG_L
#include <debug_l.h>

#include <boost/program_options.hpp>

using namespace mru;
namespace po = boost::program_options;

int
main(int argc, char **argv)
{
  FO("main(int argc, char **argv)");

  FilePath config_file;

  po::options_description desc("Command line parameters");
  desc.add_options()
    ("help,h", "show help message")
    ("config,c", po::value<FilePath>(&config_file), "configuration file to use")
    ;

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 0;
    }
  } catch (boost::program_options::unknown_option &ue) {
    std::cerr << "Unknown option specified. \n" << desc << std::endl;
    return 1;
  }

  //try {
    MruCore::Pointer core = boost::make_shared<MruCore>();  

    if (vm.count("config"))
      core->loadConfiguration(config_file);

    return core->start(argc, argv);
  //} catch (MruCore::Exception &ce) {
  //  std::cerr << "Core exception catched during program execution: \n" << glue_cast<std::string>(ce.getMessage()) << std::endl;
  //  return -1;
  //} catch (MruException &me) {
  //  std::cerr << "MRU exception catched during program execution: \n" << glue_cast<std::string>(me.getMessage()) << std::endl;
  //  return -1;
  //}
}

