add_library(materials STATIC Lambertian.cpp Metal.cpp)

target_include_directories(materials
    PUBLIC ${PROJECT_SOURCE_DIR}/includes/Materials
)