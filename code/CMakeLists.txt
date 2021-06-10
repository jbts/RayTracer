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

project(RayTracerExecutable)
add_executable(ray ray.cpp)

add_subdirectory(core)
add_subdirectory(geom)
add_subdirectory(light)
add_subdirectory(parsing)
add_subdirectory(image)
add_subdirectory(logging)
add_subdirectory(raygen)
add_subdirectory(spatial)

# From
# https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
  target_link_libraries(ray PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(ray PUBLIC
                           ${CODE_DIR}
                           ${CODE_DIR}/core
                           ${CODE_DIR}/geom
                           ${CODE_DIR}/light
                           ${CODE_DIR}/parsing
                           ${CODE_DIR}/stb_image
                           ${CODE_DIR}/image
                           ${CODE_DIR}/logging
                           ${CODE_DIR}/raygen
                           ${CODE_DIR}/spatial
)

target_link_libraries(ray PUBLIC core geom light parsing logging image raygen spatial)
