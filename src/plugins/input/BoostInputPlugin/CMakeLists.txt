cmake_minimum_required (VERSION 2.8)

add_library (BoostInputPlugin MODULE "BoostInputPlugin.cpp")
target_link_libraries (BoostInputPlugin FileIterator ${LIBS})

add_library (BoostInputPluginShared SHARED "BoostInputPlugin.cpp")
target_link_libraries (BoostInputPluginShared FileIterator ${LIBS})

