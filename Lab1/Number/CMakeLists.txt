cmake_minimum_required(VERSION 3.10)

project(Number VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Number Number.cpp)
add_compile_options("-fpic")
