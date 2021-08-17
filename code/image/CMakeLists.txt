add_library(image ToneMap.cpp ToneMapBasicClamp.cpp ToneMapAvgLumScale.cpp ToneMapModifyRed.cpp ToneMapModifyGreen.cpp ToneMapModifyBlue.cpp Image.cpp)

target_include_directories(image PUBLIC ${PROJECT_SOURCE_DIR})
