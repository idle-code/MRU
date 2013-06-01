cmake_minimum_required (VERSION 2.8)

add_library (cppunit SHARED IMPORTED)
set_target_properties(cppunit PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libcppunit.a")

add_definitions (-DSINGLE_TEST_MODE)

add_executable (unicode_path_test "unicode_path_test.cpp")
target_link_libraries (unicode_path_test cppunit debug_l)
add_test (unicode_path_test unicode_path_test)

add_executable (metatag_test "metatag_test.cpp")
target_link_libraries (metatag_test metatag cppunit debug_l)
add_test (metatag_test metatag_test)

