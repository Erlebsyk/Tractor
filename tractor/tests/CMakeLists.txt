cmake_minimum_required(VERSION 3.26.0)
project(tractor_tests VERSION 0.2.0 DESCRIPTION "Tests for the Tractor game engine" LANGUAGES CXX C)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(HeaderFiles)
set(SourceFiles
	tests_externals.cpp
    tests_tractor.cpp
	testS_tractor_events.cpp
)
add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles})

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	CXX_STANDARD 17
	C_STANDARD 17
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_link_libraries(${PROJECT_NAME} PUBLIC
	tractor
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})