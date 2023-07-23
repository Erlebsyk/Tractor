cmake_minimum_required(VERSION 3.26.0)
project(tractor VERSION 0.1.0 DESCRIPTION "Simple Game Engine" LANGUAGES CXX C)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(SourceFiles
	src/tractor.cpp
	src/application.cpp
	src/logger.cpp
)
set(IncludeFiles
	include/tractor.h

	include/tractor/application.h
	include/tractor/logger.h

	include/tractor/events/event.h
	include/tractor/events/event_application.h
	include/tractor/events/event_key.h
	include/tractor/events/event_mouse.h
)
add_library(${PROJECT_NAME} ${SourceFiles} ${IncludeFiles})

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

## Include the include directory to simplify the include paths (i.e. removes the need to specify '<tractor/...>' inside the library)
target_include_directories(${PROJECT_NAME} PRIVATE
	include/tractor
)
set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 1
	CXX_STANDARD 17
	C_STANDARD 17
)

target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

add_subdirectory(externals/glm)
add_subdirectory(externals/spdlog)
add_subdirectory(externals/googletest)
add_subdirectory(tests)

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)