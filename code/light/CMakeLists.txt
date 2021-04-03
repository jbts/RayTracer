add_library(light Material.cpp Intensity.cpp Light.cpp Shading.cpp AmbientLight.cpp PointLight.cpp DirectionalLight.cpp SpotLight.cpp)

target_include_directories(light PUBLIC ${PROJECT_SOURCE_DIR})
