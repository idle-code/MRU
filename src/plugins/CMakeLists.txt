cmake_minimum_required (VERSION 2.8)

add_library (MruPlugin "MruPlugin.cpp")
set (LIBS ${LIBS} MruPlugin)

add_subdirectory ("ui")
add_subdirectory ("input")
add_subdirectory ("output")
add_subdirectory ("tags")

