add_subdirectory(Materials)
add_library(ray_comp STATIC Image.cpp Vec.cpp Matrix.cpp ImageFilter.cpp Ray.cpp Material.cpp Shape.cpp Camera.cpp Scene.cpp)

target_include_directories(ray_comp
    PUBLIC ${PROJECT_SOURCE_DIR}/includes
)