cmake_minimum_required (VERSION 2.8)

add_library (GenericBoost MODULE "GenericBoost.cpp")
target_link_libraries (GenericBoost ${LIBS})
#target_link_libraries (GenericBoostFSDriver ${LIBS} plugin_manager)

