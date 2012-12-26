cmake_minimum_required (VERSION 2.8)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
set (CMAKE_CXX_FLAGS "-g -Wall")
include_directories ("./")
include_directories ("/usr/local/include")
link_directories ("/usr/local/lib")

find_package (ICU 4.8 COMPONENTS uc REQUIRED)
include_directories (${ICU_INCLUDE_DIRS})
set (LIBS ${LIBS} ${ICU_LIBRARIES})

find_package (wxWidgets COMPONENTS core base REQUIRED)
include_directories (${wxWidgets_INCLUDE_DIRS})
set (LIBS ${LIBS} ${wxWidgets_LIBRARIES})
include ("${wxWidgets_USE_FILE}")

find_package (SigC++ 2.2 REQUIRED)
include_directories (${SigC++_INCLUDE_DIRS})
set (LIBS ${LIBS} ${SigC++_LIBRARIES})

find_package (Boost 1.4.8 COMPONENTS program_options locale REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})
set (LIBS ${LIBS} ${Boost_LIBRARIES})

if (NOT TARGET debug_l)
  add_library (debug_l SHARED IMPORTED)
  set_target_properties(debug_l PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libdebug_l.a")
  add_definitions (-DDEBUG_L)
  set (LIBS ${LIBS} debug_l)
endif()

#TODO: make registry library
add_subdirectory ("data_tree")
include_directories ("data_tree")
set (LIBS ${LIBS} registry)

add_subdirectory ("plugin_manager")
include_directories ("plugin_manager")
set (LIBS ${LIBS} plugin_manager)

add_subdirectory ("plugins")
include_directories ("plugins")

add_executable (dt_test "dt_test.cpp")
target_link_libraries (dt_test ${LIBS}) 

add_executable (mru "main.cpp" "core.cpp")
target_link_libraries (mru ${LIBS})

