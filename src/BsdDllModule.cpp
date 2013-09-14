#include "BsdDllModule.hpp"
#include <boost/make_shared.hpp>
#include <dlfcn.h>

namespace mru
{

DllModule::Pointer
BsdDllModule::create(void)
{
  return boost::make_shared<BsdDllModule>();
}

/* ------------------------------------------------------------------------- */

BsdDllModule::~BsdDllModule(void)
{
  unLoad();
}

void
BsdDllModule::load(const FilePath &module_file)
{
  FO("BsdDllModule::load(const FilePath &module_file)");
  module_handle = dlopen(module_file.c_str(), RTLD_LAZY); //RTLD_NOW);
  if(module_handle == NULL)
    throw Exception(UnicodeString("Couldn't open '") + module_file.c_str() + "' as dynamic module: " + dlerror());
}

bool
BsdDllModule::isLoaded(void) const
{
  return module_handle != NULL;
}

void
BsdDllModule::unLoad(void)
{
  if (module_handle == NULL)
    return;
  
  int result = dlclose(module_handle);
  module_handle = NULL;
  if (0 != result)
    throw Exception(UnicodeString("Error while closing dynamic module: ") + dlerror());
}

void *
BsdDllModule::getSymbol(const char *symbol)
{
  FO("BsdDllModule::getSymbol(const char *symbol)");
  if (!isLoaded())
    throw Exception("Module not loaded");
  return dlsym(module_handle, symbol);
}

} /* namespace mru */

