cmake_minimum_required(VERSION 3.26.0)
project(tractor VERSION 0.3.13 DESCRIPTION "Simple Game Engine" LANGUAGES CXX C)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(HeaderFiles
	src/sdl_hook_events.hpp
	src/sdl_hook.hpp
)
set(SourceFiles
	src/tractor.cpp
	src/events.cpp
	src/application.cpp
	src/logger.cpp
	src/sdl_hook_events.cpp
	src/sdl_hook.cpp
	src/tractor_pch.cpp
	src/window.cpp

	src/event_types/event_base.cpp
	src/event_types/event_application.cpp
	src/event_types/event_audio.cpp
	src/event_types/event_controller.cpp
	src/event_types/event_display.cpp
	src/event_types/event_gesture.cpp
	src/event_types/event_joystick.cpp
	src/event_types/event_keyboard.cpp
	src/event_types/event_mouse.cpp
	src/event_types/event_render.cpp
	src/event_types/event_system.cpp
	src/event_types/event_touch.cpp
	src/event_types/event_window.cpp
)
set(IncludeFiles
	include/tractor.hpp

	include/tractor/application.hpp
	include/tractor/entry_point.hpp
	include/tractor/events.hpp
	include/tractor/logger.hpp
	include/tractor/logger.inl
	include/tractor/window.hpp

	include/tractor/utils/bits.hpp
	include/tractor/utils/bits.inl

	include/tractor/event_types/event_base.hpp
	include/tractor/event_types/event_application.hpp
	include/tractor/event_types/event_audio.hpp
	include/tractor/event_types/event_controller.hpp
	include/tractor/event_types/event_display.hpp
	include/tractor/event_types/event_gesture.hpp
	include/tractor/event_types/event_joystick.hpp
	include/tractor/event_types/event_keyboard.hpp
	include/tractor/event_types/event_mouse.hpp
	include/tractor/event_types/event_render.hpp
	include/tractor/event_types/event_system.hpp
	include/tractor/event_types/event_touch.hpp
	include/tractor/event_types/event_window.hpp
)
add_library(${PROJECT_NAME} ${SourceFiles} ${IncludeFiles})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/tractor_pch.hpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/tractor>
	$<INSTALL_INTERFACE:include/tractor>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:src>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 1
	CXX_STANDARD 17
	C_STANDARD 17
)

set(SDL_TEST OFF)
set(SDL_SHARED ON)
set(SDL_STATIC OFF)
set(SDL_STATIC_LIBS OFF)

target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC eventpp)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3 SDL3::SDL3main)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

add_subdirectory(externals/eventpp)
add_subdirectory(externals/glm)
add_subdirectory(externals/spdlog)
add_subdirectory(externals/SDL EXCLUDE_FROM_ALL)
add_subdirectory(externals/googletest)
add_subdirectory(tests)

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)