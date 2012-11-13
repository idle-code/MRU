cmake_minimum_required (VERSION 2.8)

add_definitions (-DDEBUG_L)
add_library (test_module1 MODULE "test_module1.cpp")
add_library (test_module2 MODULE "test_module2.cpp")
add_executable (load_test "load_test.cpp")
target_link_libraries (load_test data_tree plugin_manager debug_l)
target_link_libraries (test_module1 data_tree plugin_manager debug_l)
target_link_libraries (test_module2 data_tree plugin_manager debug_l)

