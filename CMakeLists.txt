cmake_minimum_required(VERSION 3.31)
project(TRPG-demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

set(TRPG_SRC
	src/battle.cxx
	src/being.cxx
	src/equipment.cxx
	src/simulation.cxx
	src/status.cxx
	src/util.cxx)

#[[
include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.0.0
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM)
FetchContent_MakeAvailable(SFML)
]]

include_directories(hdr)

add_executable(${PROJECT_NAME} src/main.cxx)
add_library(trpg ${TRPG_SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE trpg)
target_precompile_headers(${PROJECT_NAME} PRIVATE hdr/pch.hxx)

# target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
