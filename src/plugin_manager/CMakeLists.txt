cmake_minimum_required (VERSION 2.8)

include_directories ("./")
add_subdirectory ("tests")
#add_executable (hello "hello.cpp")
#target_link_libraries (hello variant)
add_library (plugin_manager "plugin_manager.cpp")
target_link_libraries (plugin_manager debug_l)

