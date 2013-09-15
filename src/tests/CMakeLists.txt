cmake_minimum_required (VERSION 2.8)

enable_testing()

find_package (CppUnit REQUIRED)
include_directories (${CPPUNIT_INCLUDE_DIRS})
set (LIBS ${LIBS} ${CPPUNIT_LIBRARIES})

set (LIBS ${LIBS} MruPlugin)

add_definitions (-DSINGLE_TEST_MODE)

add_executable (UnicodeStringIterator_tests "UnicodeStringIterator_tests.cpp")
target_link_libraries (UnicodeStringIterator_tests UnicodeStringIterator ${LIBS})
add_test (UnicodeStringIterator_tests UnicodeStringIterator_tests)

add_executable (StdIteratorAdapter_tests "StdIteratorAdapter_tests.cpp")
target_link_libraries (StdIteratorAdapter_tests ${LIBS})
add_test (StdIteratorAdapter_tests StdIteratorAdapter_tests)

add_executable (StateMachine_tests "StateMachine_tests.cpp")
target_link_libraries (StateMachine_tests ${LIBS})
add_test (StateMachine_tests StateMachine_tests)

# File Iterators tests:
add_library (MockFileIterator "MockFileIterator.cpp")
target_link_libraries (MockFileIterator FileIterator)

add_executable (FilteringFileIterator_tests "FilteringFileIterator_tests.cpp")
target_link_libraries (FilteringFileIterator_tests FileIterator MockFileIterator ${LIBS})
add_test (FilteringFileIterator_tests FilteringFileIterator_tests)

add_executable (SortingFileIterator_tests "SortingFileIterator_tests.cpp")
target_link_libraries (SortingFileIterator_tests FileIterator MockFileIterator ${LIBS})
add_test (SortingFileIterator_tests SortingFileIterator_tests)

# InputPlugin tests:
add_executable (BoostInput_tests "BoostInput_tests.cpp" "InputPlugin_tests.cpp")
target_link_libraries (BoostInput_tests BoostInputShared FileIterator)
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

add_executable (TokenizerBase_tests "TokenizerBase_tests.cpp")
target_link_libraries (TokenizerBase_tests TokenizerBase ${LIBS})
add_test (TokenizerBase_tests TokenizerBase_tests)

add_executable (MetatagExpressionTokenizer_tests "MetatagExpressionTokenizer_tests.cpp")
target_link_libraries (MetatagExpressionTokenizer_tests MetatagExpressionTokenizer ${LIBS})
add_test (MetatagExpressionTokenizer_tests MetatagExpressionTokenizer_tests)

add_executable (MetatagExpressionLexer_tests "MetatagExpressionLexer_tests.cpp")
target_link_libraries (MetatagExpressionLexer_tests MetatagExpressionLexer MetatagExpressionTokenizer ${LIBS})
add_test (MetatagExpressionLexer_tests MetatagExpressionLexer_tests)

add_executable (MetatagExpressionParser_tests "MetatagExpressionParser_tests.cpp")
target_link_libraries (MetatagExpressionParser_tests ${LIBS} MetatagExpressionTokenizer MetatagExpressionLexer MetatagExpressionParser)
add_test (MetatagExpressionParser_tests MetatagExpressionParser_tests)

add_executable (MetatagExpression_tests "MetatagExpression_tests.cpp")
target_link_libraries (MetatagExpression_tests ${LIBS} MockFileIterator MetatagBase MetatagExpression MetatagExpressionTokenizer MetatagExpressionLexer MetatagExpressionParser)
add_test (MetatagExpression_tests MetatagExpression_tests)

# Other:

add_library (TestModule SHARED "TestModule.cpp")
target_link_libraries (TestModule ${CMAKE_DL_LIBS})

add_executable (DllModule_tests "DllModule_tests.cpp")
target_link_libraries (DllModule_tests BsdDllModule ${LIBS})
add_test (DllModule_tests DllModule_tests)

add_executable (PluginManager_tests "PluginManager_tests.cpp")
target_link_libraries (PluginManager_tests ${LIBS})
add_test (PluginManager_tests PluginManager_tests)

add_executable (DynamicPluginManager_tests "DynamicPluginManager_tests.cpp")
target_link_libraries (DynamicPluginManager_tests ${LIBS})
add_test (DynamicPluginManager_tests DynamicPluginManager_tests)

add_executable (MruCore_tests "MruCore_tests.cpp")
target_link_libraries (MruCore_tests MruCore ${LIBS})
add_test (MruCore_tests MruCore_tests)

add_executable (glue_tests "glue_tests.cpp")
target_link_libraries (glue_tests ${LIBS})
add_test (glue_tests glue_tests)

