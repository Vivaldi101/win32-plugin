# Ensure plugins directory exists
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/plugins")

add_library(myplugin SHARED plugin.cpp plugin.h)

set_target_properties(myplugin PROPERTIES
    OUTPUT_NAME "plugin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)

# Print info messages during configure
message(STATUS "myplugin RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_BINARY_DIR}/plugins")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
