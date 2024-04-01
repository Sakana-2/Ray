#pragma once

#include <string>
#include <memory>

#include "Vec.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Shape.hpp"
#include "Light.hpp"

class Scene
{
private:
    std::unique_ptr<Camera> _camera;
    std::unique_ptr<Image> _image;
    std::unique_ptr<Shape> _world;
    std::shared_ptr<Lights> _lights;
    Vec3 _backColor;
    const char* _fname;
    int _samples;
public:
    Scene(int height, int width, int samples, const char* fname);
    void build();
    Vec3 background(const Vec3& d) const;
    Vec3 backgroundSky(const Vec3& d) const;
    void render();
};
