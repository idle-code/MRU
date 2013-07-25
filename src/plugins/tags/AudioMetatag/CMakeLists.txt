cmake_minimum_required (VERSION 2.8)

#find_package (Metataglib REQUIRED)
#include_directories (${TAGLIB_INCLUDE_DIRS})
#set (LIBS ${LIBS} ${TAGLIB_LIBRARIES})

include_directories ("/usr/include")
set (LIBS ${LIBS} "-ltag")

add_library (AudioMetatag MODULE "AudioMetatag.cpp")
target_link_libraries (AudioMetatag ${LIBS} plugin_manager)

