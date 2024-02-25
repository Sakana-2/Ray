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
} ;

class Material
{
public:
    virtual bool scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec,const Vec3 &vup) const = 0;
};

class Lambertian : public Material
{
private:
    Vec3 _albedo;

public:
    Lambertian(const Vec3 &c);

    virtual bool scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec,const Vec3 &vup) const override;
};

class Metal: public Material{
private:
    Vec3 _albedo;
public:
    Metal(const Vec3& c);
    virtual bool scatter(const Ray& r,const HitRec& hrec, ScatterRec& srec,const Vec3 &vup) const override;
};