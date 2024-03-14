#pragma once

#include <memory>

#include "Vec.hpp"
#include "Ray.hpp"

struct HitRec
{
    float t;         // 光線のパラメータ
    Vec3 p;          // 衝突した位置
    Vec3 n;          // 衝突した位置の法線ベクトル
    MaterialPtr mat; // 衝突した位置の材質
};

struct ScatterRec
{
    Ray ray;
    Vec3 albedo;
    Vec3 emit;
};

class Material
{
public:
    virtual bool scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec) const = 0;
};