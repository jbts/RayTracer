cmake_minimum_required(VERSION 3.10)

project(RayTracer)

set(CODE_DIR ${PROJECT_SOURCE_DIR}/code)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${CODE_DIR})
add_subdirectory(${CODE_DIR})

add_subdirectory(${TESTS_DIR})
