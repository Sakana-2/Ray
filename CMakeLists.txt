cmake_minimum_required(VERSION 3.27.2)
project(Ray CXX)
add_subdirectory(src)
add_executable(ray main.cpp)
target_link_libraries(ray ray_comp)
target_compile_features(ray PUBLIC cxx_std_17)
find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()