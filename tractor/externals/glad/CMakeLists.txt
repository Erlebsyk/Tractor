cmake_minimum_required(VERSION 3.26.0)

project(glad LANGUAGES CXX)

set(HeaderFiles
	include/glad/glad.h
	include/KHR/khrplatform.h
)

set(SourceFiles
	src/glad.c
)

add_library(${PROJECT_NAME} STATIC ${HeaderFiles} ${SourceFiles})

target_include_directories(${PROJECT_NAME} PUBLIC include)

