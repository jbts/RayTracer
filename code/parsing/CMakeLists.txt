add_library(parsing Parser.cpp SceneData.cpp)

target_include_directories(parsing PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(parsing PUBLIC light)
