cmake_minimum_required(VERSION 3.26.0)
project(tractor_project)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

add_subdirectory(tractor)
add_subdirectory(sandbox)