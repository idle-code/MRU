cmake_minimum_required (VERSION 2.8)

find_package (wxWidgets 2.9 COMPONENTS core base REQUIRED)
include_directories (${wxWidgets_INCLUDE_DIRS})
include ("${wxWidgets_USE_FILE}")
#message (STATUS ${wxWidgets_INCLUDE_DIRS})

add_library (wxWidgetsUi MODULE "wxWidgetsUi.cpp" "MainWindow.cpp" "PathValidator.cpp")
target_link_libraries (wxWidgetsUi ${wxWidgets_LIBRARIES} ${LIBS})

