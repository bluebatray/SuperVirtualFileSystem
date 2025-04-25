cmake_minimum_required(VERSION 3.10)
project(VirtualFileSystemApp)

# Add source to this project's executable.
add_executable(VirtualFileSystem 
    "src/main.cpp"
    "src/gui.cpp" 
    "src/io/console_output.cpp"
    "src/io/console_input.cpp"
    "src/commands/copy_command.cpp"
 "src/commands/command_manager.cpp"
   "src/filesystem/file_system.cpp" "src/commands/make_directory_command.cpp" "src/commands/list_directory_command.cpp" "src/commands/prompt_command.cpp")

# Ensure VirtualFileSystem is properly defined before linking
if (NOT TARGET VirtualFileSystem)
    message(FATAL_ERROR "Executable VirtualFileSystem not created")
endif()

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET VirtualFileSystem PROPERTY CXX_STANDARD 20)
#endif()

# C++ 23
target_compile_features(VirtualFileSystem PRIVATE cxx_std_23)

target_link_libraries(VirtualFileSystem PRIVATE virtual_file_system_lib)

# Ensure DLL is copied next to the EXE after building
add_custom_command(TARGET VirtualFileSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:virtual_file_system_lib>
    $<TARGET_FILE_DIR:VirtualFileSystem>
)