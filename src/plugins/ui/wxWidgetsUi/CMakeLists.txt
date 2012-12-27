cmake_minimum_required (VERSION 2.8)

add_library (wxWidgetsUi MODULE "wxWidgetsUi.cpp" "MainWindow.cpp" "TreeStaticBox.cpp" "FileListStaticBox.cpp" "SettingsStaticBox.cpp")
#target_link_libraries (wxWidgetsUi ${LIBS} plugin_manager)
target_link_libraries (wxWidgetsUi ${LIBS})

