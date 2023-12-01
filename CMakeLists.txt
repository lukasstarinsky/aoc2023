cmake_minimum_required(VERSION 3.26)
project(aoc2023)

set(CMAKE_CXX_STANDARD 23)

add_executable(aoc2023
    src/Main.cpp
    src/AOC.hpp

    src/Day1.cpp
)

file(GLOB_RECURSE INPUT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.txt)
file(COPY ${INPUT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})