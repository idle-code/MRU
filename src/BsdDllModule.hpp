#ifndef BSD_DLL_MODULE
#define BSD_DLL_MODULE

#include "DllModule.hpp"

namespace mru
{

class BsdDllModule : public DllModule {
public:
  static DllModule::Pointer create(void);
public:
  //BsdDllModule(void);
  ~BsdDllModule(void);

  void load(const FilePath &module_file);
  bool isLoaded(void) const;
  void unLoad(void);

  void* getSymbol(const char *symbol);

private:
  void *module_handle;
};

} /* namespace mru */

#endif /* BSD_DLL_MODULE */

