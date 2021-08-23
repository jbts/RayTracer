add_library(image Image.cpp)

target_include_directories(image PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(image PUBLIC core logging)