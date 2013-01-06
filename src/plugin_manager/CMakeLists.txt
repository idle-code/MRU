cmake_minimum_required (VERSION 2.8)

include_directories ("./")
#add_executable (hello "hello.cpp")
#target_link_libraries (hello variant)
add_library (dynamic_module "dynamic_module.cpp" "dynamic_module_bsd.cpp")
target_link_libraries (dynamic_module ${LIBS})
set (LIBS ${LIBS} dynamic_module)

add_library (plugin_manager "plugin_manager.cpp")
target_link_libraries (plugin_manager ${LIBS})
set (LIBS ${LIBS} plugin_manager)

add_subdirectory ("tests")

