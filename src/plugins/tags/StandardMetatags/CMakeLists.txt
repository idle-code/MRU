cmake_minimum_required (VERSION 2.8)

add_library (StandardMetatags MODULE "StandardMetatags.cpp" "CountMetatag.cpp" "ExtMetatag.cpp" "NameMetatag.cpp" "DirMetatag.cpp" "TextCaseMetatag.cpp" "SizeMetatag.cpp" "FormatMetatag.cpp")
target_link_libraries (StandardMetatags ${LIBS})

