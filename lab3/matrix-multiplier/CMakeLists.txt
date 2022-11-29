cmake_minimum_required(VERSION 3.10)

project(matrix VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(matrix main.cpp MatrixMultiplier.cpp)