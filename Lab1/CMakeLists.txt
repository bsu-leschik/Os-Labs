cmake_minimum_required(VERSION 3.10)

project(Libraries VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Number)
add_subdirectory(Vector)

add_executable(Libraries main.cpp)

target_link_libraries(Libraries PUBLIC Number Vector)

target_include_directories(Libraries PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_BINARY_DIR}/Number"
        "${PROJECT_BINARY_DIR}/Vector"
        )



