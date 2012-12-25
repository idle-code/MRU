cmake_minimum_required (VERSION 2.8)

add_library (TextUi MODULE "TextUi.cpp")
target_link_libraries (TextUi ${LIBS} plugin_manager)

