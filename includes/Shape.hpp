#pragma once

#include <memory>
#include <vector>

#include "Util.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Shape
{
public:
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const = 0;
};


class Sphere : public Shape
{
private:
    Vec3 _center;
    float _radius;
    MaterialPtr _material;
public:
    Sphere();
    Sphere(const Vec3 &c, float r, const MaterialPtr& mat);
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const override;
};

class ShapeList : public Shape
{
private:
    std::vector<ShapePtr> _list;
public:
    ShapeList();
    void add(const ShapePtr& shape);
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const override;
};