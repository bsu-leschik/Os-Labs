project(Vector VERSION 1.0)

add_library(Vector SHARED Vector.cpp Vector.h)

target_link_libraries(Vector PUBLIC Number)

target_include_directories(Vector PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_BINARY_DIR}/Number"
        )