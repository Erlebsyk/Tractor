cmake_minimum_required(VERSION 3.26.0)
project(sandbox VERSION 0.1.0 DESCRIPTION "Sandbox for the Tractor game engine" LANGUAGES CXX C)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(HeaderFiles
		src/sandbox.hpp
)
set(SourceFiles
		src/sandbox.cpp
)
add_executable(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	CXX_STANDARD 17
	C_STANDARD 17
)

target_link_libraries(${PROJECT_NAME} PUBLIC tractor)