#include <iostream>
#include "Light.hpp"

void Lights::add(const std::shared_ptr<BoundedPlane> &shape)
{
    _list.push_back(shape);
}

void Lights::sample(const Vec3 &x, LightRec &lrec)
{
    // 面光源のみ　一様サンプリング
    float sum = 0;
    for (auto &p : _list)
    {
        sum += p->area();
    }

    float r = drand48(), s = 0, t = 0;
    for (auto &p : _list) //複数の光源を用いてのNEEの計算についてはもう一度考え直す必要あり
    {
        t = s + p->area() / sum;
        if (s < r || r < t)
        {
            HitRec hrec;
            ScatterRec srec;

            hrec.p = p->sample();
            Ray rrr(x, hrec.p - x);
            hrec.t = 1;
            hrec.n = p->n(rrr);
            hrec.mat = p->mat().value();
            
            hrec.mat->scatter(rrr, hrec, srec);

            lrec.xl = hrec.p;
            lrec.pa = 1 / sum;
            lrec.n = hrec.n;
            lrec.emit = srec.emit;
            break;
        }
        s = t;
    }
}

bool Lights::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    HitRec temp_rec;
    bool hit_anything = false;
    float closest_so_far = t1;
    for (auto &p : _list)
    {
        if (p->hit(r, t0, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            hrec = temp_rec;
        }
    }

    return hit_anything;
}
