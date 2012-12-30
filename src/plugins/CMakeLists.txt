cmake_minimum_required (VERSION 2.8)

add_library (mru_plugin "MruPlugin.cpp")
set (LIBS ${LIBS} mru_plugin)

add_subdirectory ("ui")
add_subdirectory ("filesystem")
add_subdirectory ("tags")

