cmake_minimum_required (VERSION 2.8)

include_directories ("./")
include_directories ("/usr/local/include")
link_directories ("/usr/local/lib")
if (NOT TARGET debug_l)
  add_library (debug_l SHARED IMPORTED)
  set_target_properties(debug_l PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libdebug_l.a")
  add_definitions (-DDEBUG_L)
endif()

add_subdirectory ("data_tree")
include_directories ("data_tree")
add_subdirectory ("plugin_manager")
include_directories ("plugin_manager")
add_subdirectory ("plugins")
include_directories ("plugins")

#add_library (debug_l "debug_l/debug_l.cpp")

add_executable (dt_test "dt_test.cpp")
target_link_libraries (dt_test debug_l registry)

