cmake_minimum_required (VERSION 2.8)

add_library (BoostOutput MODULE "BoostOutput.cpp")
target_link_libraries (BoostOutput ${LIBS})

add_library (BoostOutputShared SHARED "BoostOutput.cpp")
target_link_libraries (BoostOutputShared FileIterator ${LIBS})

