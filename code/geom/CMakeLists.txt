add_library(geom Primitive.cpp Sphere.cpp Plane.cpp Triangle.cpp NormalTriangle.cpp Ray.cpp HitInfo.cpp Circle.cpp)

target_include_directories(geom PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(geom PUBLIC core)
