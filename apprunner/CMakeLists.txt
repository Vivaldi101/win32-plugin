add_executable(apprunner main.cpp)

add_dependencies(apprunner myplugin)

# Set working directory to where the plugin DLL will be
set_target_properties(apprunner PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

add_custom_command(TARGET apprunner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/plugins/$<CONFIG>/plugin.dll"
        "$<TARGET_FILE_DIR:apprunner>/plugin.dll"
)
