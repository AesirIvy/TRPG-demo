cmake_minimum_required(VERSION 3.31)
project(TRPG-demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(hdr)

add_executable(${PROJECT_NAME} src/main.cxx)
add_library(status src/battle.cxx src/being.cxx src/equipment.cxx src/simulation.cxx)
target_link_libraries(${PROJECT_NAME} PRIVATE status)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
