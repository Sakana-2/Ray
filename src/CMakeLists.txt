add_library(ray_comp STATIC Image.cpp Vec.cpp Matrix.cpp ImageFilter.cpp Ray.cpp Shape.cpp Light.cpp Camera.cpp Scene.cpp Materials/Lambertian.cpp Materials/Specular.cpp)
target_compile_features(ray_comp PUBLIC cxx_std_17)
target_include_directories(ray_comp
    PUBLIC ${PROJECT_SOURCE_DIR}/includes
)