cmake_minimum_required (VERSION 2.8)

add_library (StandardTags MODULE "StandardTags.cpp")
target_link_libraries (StandardTags ${LIBS} plugin_manager)

