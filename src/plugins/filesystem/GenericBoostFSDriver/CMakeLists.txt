cmake_minimum_required (VERSION 2.8)

add_library (GenericBoostFSDriver MODULE "GenericBoostFSDriver.cpp")
target_link_libraries (GenericBoostFSDriver ${LIBS} plugin_manager)

