add_library(spatial Scene.cpp BVHNode.cpp BVHLeafNode.cpp BVHBoundingNode.cpp XYZBounds.cpp)

target_include_directories(spatial PUBLIC ${PROJECT_SOURCE_DIR})
