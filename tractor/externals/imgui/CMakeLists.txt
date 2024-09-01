cmake_minimum_required(VERSION 3.26.0)

project(imgui LANGUAGES CXX)

set(HeaderFiles
	imgui/imconfig.h
	imgui/imgui.h
	imgui/imgui_internal.h
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h

	imgui/backends/imgui_impl_sdl2.h
	imgui/backends/imgui_impl_sdlrenderer2.h
)

set(SourceFiles
	imgui/imgui.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_widgets.cpp
	imgui/imgui_demo.cpp
	imgui/imgui_tables.cpp

	imgui/backends/imgui_impl_sdl2.cpp
	imgui/backends/imgui_impl_sdlrenderer2.cpp
)

add_library(${PROJECT_NAME} STATIC ${HeaderFiles} ${SourceFiles})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3 SDL3::SDL3main)

target_include_directories(${PROJECT_NAME} PUBLIC imgui)
target_include_directories(${PROJECT_NAME} PUBLIC imgui/backends)