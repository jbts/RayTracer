add_library(image ToneMap.cpp Image.cpp)

target_include_directories(image PUBLIC ${PROJECT_SOURCE_DIR})
