cmake_minimum_required (VERSION 2.8)

enable_testing()

find_package (CppUnit REQUIRED)
include_directories (${CPPUNIT_INCLUDE_DIRS})
set (LIBS ${LIBS} ${CPPUNIT_LIBRARIES})

set (LIBS ${LIBS} MruPlugin)

add_definitions (-DSINGLE_TEST_MODE)

add_executable (StdIteratorAdapter_tests "StdIteratorAdapter_tests.cpp")
target_link_libraries (StdIteratorAdapter_tests ${LIBS})
add_test (StdIteratorAdapter_tests StdIteratorAdapter_tests)

# File Iterators tests:
add_library (MockFileIterator "MockFileIterator.cpp")
target_link_libraries (MockFileIterator FileIterator)

add_executable (FilteringFileIterator_tests "FilteringFileIterator_tests.cpp")
target_link_libraries (FilteringFileIterator_tests FilteringFileIterator MockFileIterator ${LIBS})
add_test (FilteringFileIterator_tests FilteringFileIterator_tests)

add_executable (SortingFileIterator_tests "SortingFileIterator_tests.cpp")
target_link_libraries (SortingFileIterator_tests SortingFileIterator MockFileIterator ${LIBS})
add_test (SortingFileIterator_tests SortingFileIterator_tests)

# InputPlugin tests:
add_executable (BoostInput_tests "BoostInput_tests.cpp" "InputPlugin_tests.cpp")
target_link_libraries (BoostInput_tests BoostInputShared)
target_link_libraries (BoostInput_tests ${LIBS})
add_test (BoostInput_tests BoostInput_tests)

# OutputPlugin tests:
add_library (MockOutput "MockOutput.cpp")
add_executable (MockOutput_tests "MockOutput_tests.cpp" "OutputPlugin_common_tests.cpp" "OutputPlugin_move_tests.cpp" "OutputPlugin_copy_tests.cpp" "OutputPlugin_link_tests.cpp")
target_link_libraries (MockOutput_tests MockOutput)
target_link_libraries (MockOutput_tests ${LIBS})
add_test (MockOutput_tests MockOutput_tests)

add_executable (BoostOutput_tests "BoostOutput_tests.cpp" "OutputPlugin_common_tests.cpp" "OutputPlugin_move_tests.cpp" "OutputPlugin_copy_tests.cpp" "OutputPlugin_link_tests.cpp")
target_link_libraries (BoostOutput_tests BoostOutputShared)
target_link_libraries (BoostOutput_tests ${LIBS})
add_test (BoostOutput_tests BoostOutput_tests)

#MetatagExpression tests:

add_executable (Tokenizer_tests "Tokenizer_tests.cpp")
target_link_libraries (Tokenizer_tests ${LIBS})
add_test (Tokenizer_tests Tokenizer_tests)

add_executable (MetatagExpressionTokenizer_tests "MetatagExpressionTokenizer_tests.cpp")
target_link_libraries (MetatagExpressionTokenizer_tests ${LIBS})
add_test (MetatagExpressionTokenizer_tests MetatagExpressionTokenizer_tests)

add_executable (MetatagExpressionLexer_tests "MetatagExpressionLexer_tests.cpp")
target_link_libraries (MetatagExpressionLexer_tests ${LIBS} MetatagExpressionTokenizer)
add_test (MetatagExpressionLexer_tests MetatagExpressionLexer_tests)

add_executable (MetatagExpressionParser_tests "MetatagExpressionParser_tests.cpp")
target_link_libraries (MetatagExpressionParser_tests ${LIBS} MetatagExpressionTokenizer)
add_test (MetatagExpressionParser_tests MetatagExpressionParser_tests)

#add_executable (MetatagExpression_tests "MetatagExpression_tests.cpp")
#target_link_libraries (MetatagExpression_tests ${LIBS})
#add_test (MetatagExpression_tests MetatagExpression_tests)

# Other:

add_executable (glue_tests "glue_tests.cpp")
target_link_libraries (glue_tests ${LIBS})
add_test (glue_tests glue_tests)

