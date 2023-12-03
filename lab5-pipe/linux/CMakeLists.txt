cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(lab5 VERSION 1.0)
add_executable(main main.cpp)

add_executable(M 1/m.cpp)
add_executable(A 2/a.cpp)
add_executable(P 3/p.cpp)
add_executable(S 4/s.cpp)
