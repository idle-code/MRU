cmake_minimum_required (VERSION 2.8)

#add_library (cppunit SHARED IMPORTED)
#set_target_properties(cppunit PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libcppunit.a")
find_package (CppUnit REQUIRED)
include_directories (${CPPUNIT_INCLUDE_DIRS})
set (LIBS ${LIBS} ${CPPUNIT_LIBRARIES})

add_definitions (-DSINGLE_TEST_MODE)

add_executable (BoostInputPlugin_test "BoostInputPlugin_test.cpp")
target_link_libraries (BoostInputPlugin_test ${LIBS})
add_test (BoostInputPlugin_test BoostInputPlugin_test)

add_executable (metatag_test "metatag_test.cpp")
target_link_libraries (metatag_test metatag ${LIBS})
add_test (metatag_test metatag_test)

add_executable (glue_test "glue_test.cpp")
target_link_libraries (glue_test ${LIBS})
add_test (gluw_test glue_test)

