cmake_minimum_required (VERSION 2.8)

include_directories ("./")
add_library (metatag "expression.cpp" "metatag.cpp")
target_link_libraries (metatag ${LIBS})
set (LIBS ${LIBS} metatag)

#add_subdirectory ("tests")

