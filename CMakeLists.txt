cmake_minimum_required(VERSION 3.18)
project(projectMBP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE "src/*.cpp")
file(GLOB_RECURSE HEADER "src/*.hpp")

add_executable(projectMBP
    ${SOURCE}
    ${HEADER}
        src/constructive/ConstructiveHeuristic.cpp
        src/constructive/ConstructiveHeuristic.hpp
)
