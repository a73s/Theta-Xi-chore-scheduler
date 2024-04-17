cmake_minimum_required(VERSION 3.5)

project("Detail Generator"
	LANGUAGES CXX)

file(GLOB SOURCE_FILES
	./src/*.cpp
	./src/*.h
	./src/*.hpp
	)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -W -pedantic-errors -g -static")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -W -pedantic-errors -s -static")

add_executable(DetailGen ${SOURCE_FILES})
