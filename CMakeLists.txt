cmake_minimum_required(VERSION 3.15)

# Project name and language
project(Virtual-Sampler LANGUAGES CXX)

# Set C++ standard (change to 17 or 20 if you like)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable debug symbols by default (can be overridden with -DCMAKE_BUILD_TYPE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Generate compile_commands.json (useful for clangd / VSCodium)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the main executable
add_executable(Virtual-Sampler
    src/main.cpp
)

# Example: add include directories
target_include_directories(Virtual-Sampler PRIVATE include)

# Example: add libraries if needed
# target_link_libraries(MyApp PRIVATE mylib)

# Example: enable warnings
if (MSVC)
    target_compile_options(Virtual-Sampler PRIVATE /W4 /permissive-)
else()
    target_compile_options(Virtual-Sampler PRIVATE -Wall -Wextra -pedantic)
endif()
