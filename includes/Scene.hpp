#pragma once

#include <string>
#include <memory>

#include "Vec.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Shape.hpp"

class Scene
{
private:
    std::unique_ptr<Camera> _camera;
    std::unique_ptr<Image> _image;
    std::unique_ptr<Shape> _world;
    Vec3 _backColor;
    Vec3 _vup;
    const char* _fname;
    int _samples;
public:
    Scene(int height, int width, int samples, const char* fname, const Vec3 &vup = Vec3(0,1,0));
    void build();
    Vec3 color(Ray& r, const Shape* world) const;
    Vec3 background(const Vec3& d) const;
    Vec3 backgroundSky(const Vec3& d) const;
    void render();
};
