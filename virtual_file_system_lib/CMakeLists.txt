cmake_minimum_required(VERSION 3.10)
project(virtual_file_system_lib)

# Create a shared library
add_library(virtual_file_system_lib SHARED 
"virtual_file_system_lib.cpp"
)

# Set include directories so the app can find the headers
target_include_directories(virtual_file_system_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# Install headers
install(FILES "virtual_file_system_lib.hpp"
    DESTINATION include)
