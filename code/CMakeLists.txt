# Based on the tutorial at
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html

# Build this project:
# From the parent directory proj3, do
#
# mkdir build
# cd build
# cmake -E env CXXFLAGS="-O3" cmake ../code
# make
# ./ray my-scene-file.txt

cmake_minimum_required(VERSION 3.10)

project(RayTracer)

add_subdirectory(core)
add_subdirectory(geom)
add_subdirectory(light)
add_subdirectory(parsing)
add_subdirectory(image)
add_subdirectory(logging)
add_subdirectory(raygen)
add_subdirectory(spatial)

add_executable(ray ray.cpp)

# From
# https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
  target_link_libraries(ray PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(ray PUBLIC
                           ${PROJECT_SOURCE_DIR}
                           ${PROJECT_SOURCE_DIR}/core
                           ${PROJECT_SOURCE_DIR}/geom
                           ${PROJECT_SOURCE_DIR}/light
                           ${PROJECT_SOURCE_DIR}/parsing
                           ${PROJECT_SOURCE_DIR}/stb_image
                           ${PROJECT_SOURCE_DIR}/image
                           ${PROJECT_SOURCE_DIR}/logging
                           ${PROJECT_SOURCE_DIR}/raygen
                           ${PROJECT_SOURCE_DIR}/spatial
)

target_link_libraries(ray PUBLIC core geom light parsing logging image raygen spatial)
