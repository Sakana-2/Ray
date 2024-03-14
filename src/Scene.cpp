#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <float.h>
#include <iostream>
#include <cmath>

#include "Scene.hpp"
#include "Util.hpp"

#include "Materials/Lambertian.hpp"
#include "Materials/Metal.hpp"

Scene::Scene(int height, int width, int samples, const char *fname)
    : _image(std::make_unique<Image>(height, width)), _samples(samples), _fname(fname)
{
}

void Scene::build()
{
    ShapeList *world = new ShapeList();
    _world.reset(world);

    _camera = std::make_unique<Camera>(Vec3(0), Vec3(0,0,-1.0f), Vec3(0, 1, 0), 90, 2);
}

Vec3 Scene::color(Ray &r, const Shape *world) const
{
    HitRec hrec;
    if (world->hit(r, 0.001f, FLT_MAX, hrec))
    {
        ScatterRec srec;
        if (hrec.mat->scatter(r, hrec, srec))
        {
            return srec.albedo * color(srec.ray, world) + srec.emit; // 要素ごとの積
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
    float jitter_length = 1.0 / float(_samples);
    int s2 = _samples * _samples;
#pragma omp parallel for schedule(dynamic, 1) num_threads(NUM_THREAD)
    for (int j = 0; j < ny; j++)
    {
        std::cerr << "Rendering (y = " << j << ") " << (100.0 * j / (ny - 1)) << "%" << std::endl;
        for (int i = 0; i < nx; i++)
        {
            Vec3 c(0);
            // jittering
            for (int sy = 0; sy < _samples; sy++)
            {
                for (int sx = 0; sx < _samples; sx++)
                {
                    float u = float(i + jitter_length * (sx + drand48())) / float(nx);
                    float v = float(j + jitter_length * (sy + drand48())) / float(ny);
                    Ray r = _camera->emitRay(u, v);
                    c += color(r, _world.get());
                }
            }
            c /= s2;
            _image->set_pixel(j, i, c);
        }
    }

    //Test
    // Ray r(_camera->origin(),Vec3(0,-0.5f,-1.0f));
    // Vec3 c(0);
    // for (int i = 0; i < s2; i++)
    // {
    //     c += color(r,_world.get());
    // }
    // c /= s2;
    // std::cout << c << std::endl;
    // Vec3 pix(static_cast<unsigned char>(c[0] * 255.99f), static_cast<unsigned char>(c[1] * 255.99f), static_cast<unsigned char>(c[2] * 255.99f));
    // std::cout << pix << std::endl;
    
    stbi_write_bmp(_fname, nx, ny, sizeof(rgb), _image->data());
}
