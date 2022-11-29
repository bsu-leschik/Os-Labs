cmake_minimum_required(VERSION 3.10)

project(Vector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../Number)

add_library(Vector SHARED Vector.cpp Vector.h)

find_library(NUMBER Number ../Number/cmake-build-debug)
target_link_libraries(Vector LINK_PUBLIC ${NUMBER})

target_include_directories(Vector PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_BINARY_DIR}/Number"
        )