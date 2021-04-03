add_library(raygen PixelTraceData.cpp ViewFrame.cpp)

target_include_directories(raygen PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(raygen PUBLIC core geom)
