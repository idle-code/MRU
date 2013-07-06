cmake_minimum_required (VERSION 2.8)

add_library (mru_plugin "MruPlugin.cpp")
set (LIBS ${LIBS} mru_plugin)

add_subdirectory ("ui")
add_subdirectory ("input")
add_subdirectory ("output")
add_subdirectory ("tags")

