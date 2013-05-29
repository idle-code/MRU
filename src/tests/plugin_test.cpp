#undef NDEBUG_L
#include <debug_l.h>
#include "plugin_test.hpp"
#include <cppunit/ui/text/TestRunner.h>

/* ------------------------------------------------------------------------- */

class A_Interface {
public:
  virtual void do_work(void) = 0;
  virtual ~A_Interface(void) { }
};

class B_Interface {
public:
  virtual void do_other_work(void) = 0;
  virtual ~B_Interface(void) { }
};

/* ------------------------------------------------------------------------- */

class A_Plugin : public A_Interface {
public:
  void do_work(void)
  { FO("A_Plugin::do_work"); }
};

class B_Plugin : public B_Interface {
public:
  void do_other_work(void)
  { FO("B_Plugin::do_other_work"); }
};

class B2_Plugin : public B_Interface {
public:
  void do_other_work(void)
  { FO("B2_Plugin::do_other_work and different things"); }
};

/* ------------------------------------------------------------------------- */

void
plugin_tests::construct(void)
{
  FO("construct(void)");

  A_Interface *a_plg = NULL;
  B_Interface *b_plg = NULL;
  B_Interface *b2_plg = NULL;

  typedef plugin_manager<A_Interface> APluginManager;
  typedef plugin_manager<B_Interface> BPluginManager;
  typedef APluginManager::plugin_factory<A_Plugin> APluginFactory;
  typedef BPluginManager::plugin_factory<B_Plugin> BPluginFactory;
  typedef BPluginManager::plugin_factory<B2_Plugin> B2PluginFactory;
  
  APluginManager a_mng;
  BPluginManager b_mng;
  
  a_mng.register_factory(new APluginFactory("A_Plugin"));
  b_mng.register_factory(new BPluginFactory("B_Plugin"));
  b_mng.register_factory(new B2PluginFactory("B2_Plugin"));

  std::list<APluginFactory::typeinfo_type> a_plg_list = a_mng.available_plugins();
  std::list<BPluginFactory::typeinfo_type> b_plg_list = b_mng.available_plugins();
  for(std::list<APluginFactory::typeinfo_type>::iterator i = a_plg_list.begin(); i != a_plg_list.end(); ++i) {
    MSG(*i);
  }
  for(std::list<BPluginFactory::typeinfo_type>::iterator i = b_plg_list.begin(); i != b_plg_list.end(); ++i) {
    MSG(*i);
  }

  a_plg = a_mng.get_instance("A_Plugin");
  b_plg = b_mng.get_instance("B_Plugin");
  b2_plg = b_mng.get_instance("B2_Plugin");

  CPPUNIT_ASSERT(a_plg != NULL);
  CPPUNIT_ASSERT(b_plg != NULL);

  a_plg->do_work();
  b_plg->do_other_work();
  b2_plg->do_other_work();

  a_mng.free_instance(a_plg);
  b_mng.free_instance(b_plg);
  b_mng.free_instance(b2_plg);
}

void
plugin_tests::load(void)
{
  FO("plugin_tests::load(void)")
  A_Interface *a_plg = NULL;
  B_Interface *b_plg = NULL;

  typedef plugin_manager<A_Interface> APluginManager;
  typedef plugin_manager<B_Interface> BPluginManager;

  APluginManager a_mng;
  BPluginManager b_mng;
  
  a_mng.load_module("a_module");
  b_mng.load_module("b_module");
}

void
plugin_tests::unload(void)
{

}

void
plugin_tests::lookup(void)
{

}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(plugin_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

