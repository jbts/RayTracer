project(RayTracerTests)
add_executable(run_tests run_tests.cpp)

# Library for testing
find_package(Catch2 REQUIRED)

target_link_libraries(run_tests PUBLIC core geom image light logging parsing raygen spatial Catch2::Catch2WithMain)
