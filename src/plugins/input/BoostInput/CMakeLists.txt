cmake_minimum_required (VERSION 2.8)

add_library (BoostInput MODULE "BoostInput.cpp")
target_link_libraries (BoostInput FileIterator ${LIBS})

add_library (BoostInputShared SHARED "BoostInput.cpp")
target_link_libraries (BoostInputShared FileIterator ${LIBS})

