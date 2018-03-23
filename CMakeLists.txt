# src-level CMakeLists.

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)



# Specify the project, its version and the used language.
project(cpputil
        VERSION 1.2.1
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)



# Set some compiler optimizations (https://stackoverflow.com/a/41361741/7930415).
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")



# Set CMake variables.
include(${CMAKE_SOURCE_DIR}/cmake/SetCMakeEnvironment.cmake)



# Find all required packages.
include(${CMAKE_SOURCE_DIR}/cmake/FindPackages.cmake)



# Add the sources for the library.
add_subdirectory(${PROJECT_SOURCE_FOLDER})



# Set up testing.
enable_testing()
add_subdirectory(${PROJECT_TESTS_FOLDER})
