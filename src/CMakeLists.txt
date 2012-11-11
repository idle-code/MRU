cmake_minimum_required (VERSION 2.8)

add_definitions (-DDEBUG_L)

include_directories ("data_tree")
include_directories ("./")
include_directories ("/usr/local/include")
link_directories ("/usr/local/lib")
add_library (debug_l SHARED IMPORTED)
#add_library (debug_l "debug_l/debug_l.cpp")
set_target_properties(debug_l PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libdebug_l.a")
add_subdirectory ("data_tree")
add_subdirectory ("plugin_manager")
add_subdirectory ("plugins")

