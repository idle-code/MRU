cmake_minimum_required (VERSION 2.8)

find_package (CppUnit REQUIRED)
include_directories (${CPPUNIT_INCLUDE_DIRS})
set (LIBS ${LIBS} ${CPPUNIT_LIBRARIES})

add_definitions (-DSINGLE_TEST_MODE)

# File Iterators tests:
add_library (MockFileIterator "MockFileIterator.cpp")
target_link_libraries (MockFileIterator FileIterator)

add_executable (FilteringFileIterator_test "FilteringFileIterator_test.cpp")
target_link_libraries (FilteringFileIterator_test FilteringFileIterator MockFileIterator ${LIBS})
add_test (FilteringFileIterator_test FilteringFileIterator_test)

add_executable (SortingFileIterator_test "SortingFileIterator_test.cpp")
target_link_libraries (SortingFileIterator_test SortingFileIterator MockFileIterator ${LIBS})
add_test (SortingFileIterator_test SortingFileIterator_test)

# InputPlugin tests:
add_executable (BoostInputPlugin_test "BoostInputPlugin_test.cpp" "InputPlugin_test.cpp")
target_link_libraries (BoostInputPlugin_test BoostInputPluginShared)
target_link_libraries (BoostInputPlugin_test ${LIBS})
add_test (BoostInputPlugin_test BoostInputPlugin_test)

# OutputPlugin tests: TODO
#target_link_libraries (OutputPlugin_test BoostOutputPluginShared)
#target_link_libraries (OutputPlugin_test ${LIBS})
#add_test (OutputPlugin_test OututPlugin_test)

# Metatags tests: TODO

# Other:
add_executable (metatag_test "metatag_test.cpp")
target_link_libraries (metatag_test metatag ${LIBS})
add_test (metatag_test metatag_test)

add_executable (glue_test "glue_test.cpp")
target_link_libraries (glue_test ${LIBS})
add_test (gluw_test glue_test)

