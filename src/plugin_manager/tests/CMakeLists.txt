cmake_minimum_required (VERSION 2.8)

add_definitions (-DDEBUG_L)
add_library (test_module1 MODULE "test_module1.cpp")
add_library (test_module2 MODULE "test_module2.cpp")
add_executable (load_test "load_test.cpp")
target_link_libraries (load_test plugin_manager debug_l)
target_link_libraries (test_module1 plugin_manager debug_l)
target_link_libraries (test_module2 plugin_manager debug_l)

add_library (hello_plugin MODULE "hello_plugin.cpp")
add_executable (hello_host "hello_host.cpp")
target_link_libraries (hello_plugin registry plugin_manager debug_l)
target_link_libraries (hello_host registry plugin_manager debug_l)

