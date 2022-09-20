cmake_minimum_required(VERSION 3.10)

project(Libraries VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Libraries main.cpp)

include_directories(Number)
find_library(NUMBER Number Number/cmake-build-debug)
target_link_libraries(Libraries LINK_PUBLIC ${NUMBER})

include_directories(Vector)
find_library(VECTOR Vector Vector/cmake-build-debug)
target_link_libraries(Libraries LINK_PUBLIC  ${VECTOR})