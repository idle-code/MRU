cmake_minimum_required (VERSION 2.8)

add_definitions (-DDEBUG_L)
add_executable (load_test "load_test.cpp")
target_link_libraries (load_test plugin_manager debug_l)

