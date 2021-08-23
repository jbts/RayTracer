add_library(imagemap ImageMap.cpp ImageMapBasicClamp.cpp ImageMapNop.cpp ImageMapAvgLumScale.cpp ImageMapReinhardGlobal.cpp ImageMapUtil.cpp)

target_include_directories(imagemap PUBLIC ${PROJECT_SOURCE_DIR})
