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
#include "Materials/Specular.hpp"

#define TRACING_METHOD 1 // 0:STANDARD 1:NEE

Scene::Scene(int height, int width, int samples, const char *fname)
    : _image(std::make_unique<Image>(height, width)), _samples(samples), _fname(fname)
{
}

void Scene::build()
{
    ShapeList *world = new ShapeList();
    Lights *lights = new Lights();

    _lights.reset(lights);
    world->add(_lights);
    _world.reset(world);

    _camera = std::make_unique<Camera>(Vec3(0), Vec3(0, 0, -1), Vec3(0, 1, 0), 90, 1);
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
                    HitRec hrec;
                    Vec3 alpha(1);
                    bool first = true;
                    while (_world.get()->hit(r, 0.001f, FLT_MAX, hrec))
                    {
                        ScatterRec srec;
                        if (hrec.mat->scatter(r, hrec, srec))
                        {
#if TRACING_METHOD == 0:
                            c += alpha * srec.emit;
                            alpha *= srec.albedo;
#elif TRACING_METHOD == 1:
                            alpha *= srec.albedo;
                            if (first)
                            {
                                c += srec.emit;
                                first = false;
                            }

                            if (srec.isSpecular)
                            {
                                c += alpha * srec.emit;
                            }
                            else
                            {
                                LightRec lrec;
                                _lights.get()->sample(hrec.p, lrec);
                                HitRec hitinfo;
                                Vec3 s_dir = lrec.xl - hrec.p;
                                Ray shadowRay(hrec.p, s_dir);
                                if (!_world.get()->hit(shadowRay, 0.001f, s_dir.length(), hitinfo))
                                {
                                    float G = (-s_dir).dot(lrec.n) / s_dir.lengthSqr();
                                    c += alpha * lrec.emit * G / lrec.pa;
                                    // srec.albedo内に受け取る側でのcos項を含む
                                }
                            }
#endif

                            r = srec.ray;
                        }
                    }
                }
            }
            c /= s2;
            _image->set_pixel(j, i, c);
        }
    }

    stbi_write_bmp(_fname, nx, ny, sizeof(rgb), _image->data());
}
