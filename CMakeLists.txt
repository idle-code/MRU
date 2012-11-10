cmake_minimum_required (VERSION 2.8)
project (MRU)
set (MRU_VERSION_MAJOR 0)
set (MRU_VERSION_MINOR 1)

#configure_file ("${PROJECT_SOURCE_DIR}/mru.hpp.in" "${PROJECT_BINARY_DIR}/mru.hpp")
#include_directories ("${PROJECT_BINARY_DIR}")
add_subdirectory ("src")
#include_directories ("${PROJECT_SOURCE_DIR}/src")
#add_executable (mru main.cpp)

