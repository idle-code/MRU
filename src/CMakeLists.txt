cmake_minimum_required (VERSION 2.8)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package (ICU 4.8 REQUIRED)
include_directories (${ICU_INCLUDE_DIRS})
set (LIBS ${LIBS} ${ICU_LIBRARIES})

find_package (wxWidgets REQUIRED)
include_directories (${WXWIDGETS_INCLUDE_DIRS})
set (LIBS ${LIBS} ${WXWIDGETS_LIBRARIES})

find_package (SigC++ 2.2 REQUIRED)
include_directories (${SigC++_INCLUDE_DIRS})
set (LIBS ${LIBS} ${SigC++_LIBRARIES})

find_package (Boost REQUIRED)
include_directories (${BOOST_INCLUDE_DIRS})
set (LIBS ${LIBS} ${BOOST_LIBRARIES})

include_directories ("./")
include_directories ("/usr/local/include")
link_directories ("/usr/local/lib")
if (NOT TARGET debug_l)
  add_library (debug_l SHARED IMPORTED)
  set_target_properties(debug_l PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libdebug_l.a")
  add_definitions (-DDEBUG_L)
endif()

#TODO: make registry library
add_subdirectory ("data_tree")
include_directories ("data_tree")

add_subdirectory ("plugin_manager")
include_directories ("plugin_manager")
add_subdirectory ("plugins")
include_directories ("plugins")

add_definitions (-DDEBUG_L) # enable debugging
set (LIBS ${LIBS} debug_l registry plugin_manager)

add_executable (dt_test "dt_test.cpp")
target_link_libraries (dt_test ${LIBS}) 

add_executable (mru "main.cpp")
target_link_libraries (mru ${LIBS})

