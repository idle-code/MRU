cmake_minimum_required (VERSION 2.8)

enable_testing()

find_package (CppUnit REQUIRED)
include_directories (${CPPUNIT_INCLUDE_DIRS})
set (LIBS ${LIBS} ${CPPUNIT_LIBRARIES})

set (LIBS ${LIBS} MruPlugin)

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
add_executable (BoostInput_test "BoostInput_test.cpp" "InputPlugin_test.cpp")
target_link_libraries (BoostInput_test BoostInputShared)
target_link_libraries (BoostInput_test ${LIBS})
add_test (BoostInput_test BoostInput_test)

# OutputPlugin tests:
add_library (MockOutput "MockOutput.cpp")
add_executable (MockOutput_test "MockOutput_test.cpp" "OutputPlugin_common_test.cpp" "OutputPlugin_move_test.cpp" "OutputPlugin_copy_test.cpp" "OutputPlugin_link_test.cpp")
target_link_libraries (MockOutput_test MockOutput)
target_link_libraries (MockOutput_test ${LIBS})
add_test (MockOutput_test MockOutput_test)

add_executable (BoostOutput_test "BoostOutput_test.cpp" "OutputPlugin_common_test.cpp" "OutputPlugin_move_test.cpp" "OutputPlugin_copy_test.cpp" "OutputPlugin_link_test.cpp")
target_link_libraries (BoostOutput_test BoostOutputShared)
target_link_libraries (BoostOutput_test ${LIBS})
add_test (BoostOutput_test BoostOutput_test)

#MetatagExpression tests:
#add_executable (MetatagExpressionParser_test "MetatagExpressionParser_test.cpp")
#target_link_libraries (MetatagExpressionParser_test ${LIBS})
#add_test (MetatagExpressionParser_test MetatagExpressionParser_test)

add_executable (MetatagExpression_test "MetatagExpression_test.cpp")
target_link_libraries (MetatagExpression_test ${LIBS})
add_test (MetatagExpression_test MetatagExpression_test)

# Other:

add_executable (glue_test "glue_test.cpp")
target_link_libraries (glue_test ${LIBS})
add_test (gluw_test glue_test)

