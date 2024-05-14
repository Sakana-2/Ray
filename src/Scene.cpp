#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <float.h>
#include <iostream>
#include <cmath>
#include <time.h>

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

    Vec3 t1[3] = {Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -1.5f)};
    Vec3 t2[3] = {Vec3(-0.5f, -0.5f, -0.5f), Vec3(-0.5f, -0.5f, -1.5f), Vec3(0.5f, -0.5f, -1.5f)};
    world->add(std::make_shared<Triangle>(t1, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));
    world->add(std::make_shared<Triangle>(t2, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));

    Vec3 t3[3] = {Vec3(-0.5f, -0.5f, -0.5f), Vec3(-0.5f, 0.5f, -0.5f), Vec3(-0.5f, -0.5f, -1.5f)};
    Vec3 t4[3] = {Vec3(-0.5f, 0.5f, -1.5f), Vec3(-0.5f, -0.5f, -1.5f), Vec3(-0.5f, 0.5f, -0.5f)};
    world->add(std::make_shared<Triangle>(t3, std::make_shared<Lambertian>(Vec3(0.8, 0, 0), Vec3(0))));
    world->add(std::make_shared<Triangle>(t4, std::make_shared<Lambertian>(Vec3(0.8, 0, 0), Vec3(0))));

    Vec3 t5[3] = {Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, -0.5f, -1.5f), Vec3(0.5f, 0.5f, -1.5f)};
    Vec3 t6[3] = {Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -1.5f)};
    world->add(std::make_shared<Triangle>(t5, std::make_shared<Lambertian>(Vec3(0, 0.8, 0), Vec3(0))));
    world->add(std::make_shared<Triangle>(t6, std::make_shared<Lambertian>(Vec3(0, 0.8, 0), Vec3(0))));

    Vec3 t7[3] = {Vec3(-0.5f, 0.5f, -1.5f), Vec3(0.5f, 0.5f, -1.5f), Vec3(-0.5f, 0.5f, -0.5f)};
    Vec3 t8[3] = {Vec3(0.5f, 0.5f, -0.5f), Vec3(-0.5f, 0.5f, -0.5f), Vec3(0.5f, 0.5f, -1.5f)};
    world->add(std::make_shared<Triangle>(t7, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));
    world->add(std::make_shared<Triangle>(t8, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));

    Vec3 t9[3] = {Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -1.5f)};
    Vec3 t10[3] = {Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -1.5f), Vec3(-0.5f, -0.5f, -1.5f)};
    world->add(std::make_shared<Triangle>(t9, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));
    world->add(std::make_shared<Triangle>(t10, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));

    Vec3 t11[3] = {Vec3(-0.5f, 0.5f, -1.5f), Vec3(-0.5f, -0.5f, -1.5f), Vec3(0.5f, 0.5f, -1.5f)};
    Vec3 t12[3] = {Vec3(-0.5f, -0.5f, -1.5f), Vec3(0.5f, -0.5f, -1.5f), Vec3(0.5f, 0.5f, -1.5f)};
    world->add(std::make_shared<Triangle>(t11, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));
    world->add(std::make_shared<Triangle>(t12, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));

    world->add(std::make_shared<Sphere>(Vec3(0.24f, -0.25f, -0.7f), 0.25f, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));
    world->add(std::make_shared<Sphere>(Vec3(-0.2f, -0.25f, -1.0f), 0.25f, std::make_shared<Lambertian>(Vec3(1), Vec3(0))));

    Vec3 tl[3] = {Vec3(-0.125f, 0.499f, -0.875f), Vec3(0.125f, 0.499f, -0.875f), Vec3(0.125f, 0.499f, -1.125f)};
    Vec3 tl2[3] = {Vec3(-0.125f, 0.499f, -0.875f), Vec3(-0.125f, 0.499f, -1.125f), Vec3(0.125f, 0.499f, -1.125f)};
    lights->add(std::make_shared<Triangle>(tl, std::make_shared<Lambertian>(Vec3(0), Vec3(1))));
    lights->add(std::make_shared<Triangle>(tl2, std::make_shared<Lambertian>(Vec3(0), Vec3(1))));

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
    float start = (float)clock() / CLOCKS_PER_SEC;
    printf("[START]");
#pragma omp parallel for schedule(dynamic, 1) num_threads(NUM_THREAD)
    for (int j = 0; j < ny; j++)
    {
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
#elif TRACING_METHOD == 1:
                            if (first)
                            {
                                c += alpha * srec.emit;
                                first = false;
                            }

                            if (!first && srec.isSpecular)
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
                                    c += alpha * srec.albedo * lrec.emit * G / lrec.pa;
                                    // srec.albedo内に受け取る側でのcos項を含む
                                }
                            }
#endif
                            alpha *= srec.albedo; // これでうまくいってるのは拡散反射だから、別の素材をやるときは改良すべし
                            
                            //Russian Rurrete
                            float prr = max(srec.albedo);
                            if (drand48() >= prr)
                            {
                                break;   
                            }
                            alpha /= prr;
                            r = srec.ray;
                        }
                    }
                    // c += alpha * Vec3(1);
                }
            }
            c /= s2;
            _image->set_pixel(j, i, c);
        }
        float now = (float)clock() / CLOCKS_PER_SEC;
        float done = (float)(j + 1) / ny;
        float left_t = (now - start) / done - now;

        printf("\r[\x1b[32m%.1f\x1b[39m%% RENDERED] [\x1b[32m%.1f\x1b[39ms=\x1b[32m%.1f\x1b[39mm=\x1b[32m%.1f\x1b[39mh LEFT]         ", (100.0 * done), left_t, left_t / 60, left_t / 3600, j);
    }
    printf("\n");

    stbi_write_bmp(_fname, nx, ny, sizeof(rgb), _image->data());
}
