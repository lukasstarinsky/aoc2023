cmake_minimum_required(VERSION 3.26)
project(aoc2023)

set(CMAKE_CXX_STANDARD 23)

add_executable(aoc2023
    src/Main.cpp
    src/AOC.hpp

    src/Day1.cpp
    src/Day2.cpp
    src/Day3.cpp
    src/Day4.cpp
)

add_custom_target(copy_input_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMENT "Copying input data files..."
)
add_dependencies(aoc2023 copy_input_data)