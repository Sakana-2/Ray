#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <float.h>
#include <iostream>
#include <cmath>

#include "Scene.hpp"
#include "Util.hpp"
#include "Material.hpp"

Scene::Scene(int height, int width, int samples, const char *fname)
    : _image(std::make_unique<Image>(height, width)), _samples(samples), _fname(fname)
{
}

void Scene::build()
{
    ShapeList *world = new ShapeList();
    world->add(std::make_shared<Sphere>(
        Vec3(0, 0, -1), 0.5f,
        std::make_shared<Lambertian>(Vec3(0.1f, 0.2f, 0.5f))));
    world->add(std::make_shared<Sphere>(
        Vec3(0, -100.5, -1), 100,
        std::make_shared<Lambertian>(Vec3(0.8f, 0.8f, 0.0f))));
    _world.reset(world);

    Vec3 w(-2.0f, -1.0f, -1.0f);
    Vec3 u(4.0f, 0.0f, 0.0f);
    Vec3 v(0.0f, 2.0f, 0.0f);
    // _camera = std::make_unique<Camera>(u, v, w);
    _camera = std::make_unique<Camera>(Vec3(0),w+u/2+v/2,Vec3(0,1,0),90,2);
}

Vec3 Scene::color(Ray &r, const Shape *world) const
{
    HitRec hrec;
    if (world->hit(r, 0.001f, FLT_MAX, hrec))
    {
        ScatterRec srec;
        if (hrec.mat->scatter(r, hrec, srec))
        {
            return srec.albedo * color(srec.ray, world); // 要素ごとの積
        }
        else
        {
            return Vec3(0);
        }
    }
    return backgroundSky(r.direction());
}

Vec3 Scene::background(const Vec3 &d) const
{
    return _backColor;
}

Vec3 Scene::backgroundSky(const Vec3 &d) const
{
    Vec3 v = d.normalize();
    float t = 0.5f * (v[1] + 1.0f);
    return lerp(t, Vec3(1), Vec3(0.5f, 0.7f, 1.0f));
}

void Scene::render()
{
    build();

    int nx = _image->width();
    int ny = _image->height();
#pragma omp parallel for schedule(dynamic, 1) num_threads(NUM_THREAD)
    for (int j = 0; j < ny; j++)
    {
        std::cerr << "Rendering (y = " << j << ") " << (100.0 * j / (ny - 1)) << "%" << std::endl;
        for (int i = 0; i < nx; i++)
        {
            Vec3 c(0);
            for (int s = 0; s < _samples; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray r = _camera->emitRay(u, v);
                c += color(r, _world.get());
            }
            c /= _samples;
            _image->set_pixel(j, i, c);
        }
    }

    stbi_write_bmp(_fname, nx, ny, sizeof(rgb), _image->data());
}
