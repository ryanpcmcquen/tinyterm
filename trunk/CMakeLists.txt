cmake_minimum_required (VERSION 2.6)
project (TinyTerm)
set (TARGET_VERSION_MAJOR 0)
set (TARGET_VERSION_MINOR 1)

find_package (PkgConfig REQUIRED)
pkg_search_module (VTE REQUIRED vte)
link_directories (${VTE_LIBRARY_DIRS})
include_directories (${VTE_INCLUDE_DIRS})

configure_file ("${CMAKE_SOURCE_DIR}/config.h.in" "${CMAKE_BINARY_DIR}/config.h")

add_executable (tinyterm tinyterm.c)
target_link_libraries (tinyterm ${VTE_LIBRARIES})

install (TARGETS tinyterm
         RUNTIME DESTINATION bin)

install (FILES tinyterm.png
         DESTINATION share/pixmaps)
