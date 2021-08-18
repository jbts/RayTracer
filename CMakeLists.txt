cmake_minimum_required(VERSION 3.10)

project(RayTracer)

option(BUILD_TESTS "Should the tests be included in the build process?
                   If you'd just like to run the code, this should be
                   set to OFF. If it's set to ON, the Catch2 package is
                   required." OFF)

set(CODE_DIR ${PROJECT_SOURCE_DIR}/code)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${CODE_DIR})
add_subdirectory(${CODE_DIR})

if (BUILD_TESTS)
  add_subdirectory(${TESTS_DIR})
endif()
