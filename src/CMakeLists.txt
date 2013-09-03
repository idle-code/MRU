cmake_minimum_required (VERSION 2.8)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
set (CMAKE_CXX_FLAGS "-g -ferror-limit=3 -fPIC")
#set (CMAKE_CXX_FLAGS "-g -ferror-limit=3")
include_directories ("./")
include_directories ("/usr/local/include")
link_directories ("/usr/local/lib")

find_package (Threads REQUIRED)
set (LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})
find_package (ICU 50.1 COMPONENTS uc i18n REQUIRED)
include_directories (${ICU_INCLUDE_DIRS})
set (LIBS ${LIBS} ${ICU_LIBRARIES})

find_package (wxWidgets 2.9 COMPONENTS core base REQUIRED)
include_directories (${wxWidgets_INCLUDE_DIRS})
set (LIBS ${LIBS} ${wxWidgets_LIBRARIES})
include ("${wxWidgets_USE_FILE}")
message (STATUS ${wxWidgets_INCLUDE_DIRS})

find_package (SigC++ 2.2 REQUIRED)
include_directories (${SigC++_INCLUDE_DIRS})
set (LIBS ${LIBS} ${SigC++_LIBRARIES})

find_package (Boost COMPONENTS program_options locale system filesystem REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})
set (LIBS ${LIBS} ${Boost_LIBRARIES})

if (NOT TARGET debug_l)
  #add_library (debug_l SHARED IMPORTED)
  #set_target_properties(debug_l PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libdebug_l.a")

  add_subdirectory ("debug_l")
  include_directories ("debug_l")
  set (LIBS ${LIBS} debug_l)
  add_definitions (-DDEBUG_L)
endif()

#TODO: make registry library
#add_subdirectory ("data_tree")
#include_directories ("data_tree")
#set (LIBS ${LIBS} registry)

add_subdirectory ("plugin_manager")
include_directories ("plugin_manager")

#add_executable (dt_test "dt_test.cpp")
#target_link_libraries (dt_test ${LIBS}) 

add_subdirectory ("plugins")
include_directories ("plugins")
set (LIBS ${LIBS} plugin_manager)

#add_subdirectory ("metatag")
#include_directories ("metatag")
#set (LIBS ${LIBS} metatag)

add_library (FileIterator "FileIterator.cpp")

add_library (SortingFileIterator "SortingFileIterator.cpp")

add_library (FilteringFileIterator "FilteringFileIterator.cpp")

add_library (UnicodeStringIterator "UnicodeStringIterator.cpp")

add_library (TokenizerBase "TokenizerBase.cpp")
target_link_libraries (TokenizerBase UnicodeStringIterator ${LIBS})

add_library (MetatagBase "MetatagBase.cpp")
target_link_libraries (MetatagBase ${LIBS})

add_subdirectory ("Metatag")

add_library (MruCore "MruCore.cpp" "MruDefaultConfiguration.cpp")

add_executable (mru "main.cpp")
target_link_libraries (mru MruCore ${LIBS} ${CMAKE_DL_LIBS})
set_target_properties (mru PROPERTIES ENABLE_EXPORTS TRUE)

add_subdirectory ("tests")

