add_library(imagemap ImageMap.cpp ImageMapBasicClamp.cpp ImageMapNop.cpp ImageMapAvgLumScale.cpp ImageMapReinhardGlobal.cpp ImageMapReinhardLocal.cpp ImageMapUtil.cpp)

target_include_directories(imagemap PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(imagemap PUBLIC core image)