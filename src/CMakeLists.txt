add_library(ray_comp STATIC Image.cpp Vec.cpp Matrix.cpp ImageFilter.cpp Ray.cpp Shape.cpp Camera.cpp Scene.cpp Materials/Lambertian.cpp Materials/Specular.cpp)

target_include_directories(ray_comp
    PUBLIC ${PROJECT_SOURCE_DIR}/includes
)