cmake_minimum_required(VERSION 3.16)

project(Virtual-Sampler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/wx-install")

find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base)

add_executable(Virtual-Sampler source/src/UI/base.cpp)

target_include_directories(Virtual-Sampler PRIVATE 
  ${CMAKE_SOURCE_DIR}/source/include
  ${CMAKE_SOURCE_DIR}/source/include/UI
)

target_link_libraries(Virtual-Sampler PRIVATE wx::core wx::base)
