cmake_minimum_required(VERSION 3.16)

project(Virtual-Sampler LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(GGC_COVARGE_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Wreorder -Wunused -Wshadow -Werror=return-type")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#wxWidgets setup 
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/wx-install")
find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base)

#
add_library(miniaudio INTERFACE)

#Get source (*.cpp) files
file(GLOB_RECURSE SOURCE_FILES
  "${CMAKE_SOURCE_DIR}/source/*.cpp"
  "${CMAKE_SOURCE_DIR}/libs/miniaudio/*.c"
)

#get header (*.h, *.hpp) files
#Added the miniaudio and nlohmann-json libs here, since they're just one header
file(GLOB_RECURSE HEADER_FILES 
  "${CMAKE_SOURCE_DIR}/source/*.hpp"
)

add_executable(Virtual-Sampler ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(Virtual-Sampler PRIVATE "source/include")
target_include_directories(miniaudio INTERFACE "libs/miniaudio")

#link wxWidgets
target_link_libraries(Virtual-Sampler PRIVATE wx::core wx::base miniaudio)
