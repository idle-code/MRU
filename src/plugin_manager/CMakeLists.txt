cmake_minimum_required (VERSION 2.8)

include_directories ("./")
add_subdirectory ("tests")
#add_executable (hello "hello.cpp")
#target_link_libraries (hello variant)
add_library (plugin_manager "plugin_manager.cpp")
add_library (dynamic_module "dynamic_module.cpp" "dynamic_module_bsd.cpp")
target_link_libraries (plugin_manager dynamic_module registry debug_l)

