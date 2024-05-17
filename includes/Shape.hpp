#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "AABB.hpp"
#include "Util.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Shape
{
protected:
    std::optional<MaterialPtr> _material;
    AABB _box;

public:
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const = 0;
    std::optional<MaterialPtr> mat() const;
    AABB box() const;
};

class Sphere : public Shape
{
private:
    Vec3 _center;
    float _radius;

public:
    Sphere();
    Sphere(const Vec3 &c, float r, const MaterialPtr &mat);
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const override;
};

class Triangle : public Shape
{
private:
    Vec3 _points[3];
    Vec3 _n;
    float _area;

public:
    Triangle();
    Triangle(const Vec3 points[3], const MaterialPtr &mat);
    float area() const;
    Vec3 sample() const;
    Vec3 n(const Ray &r) const;
    bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const;
};

class ShapeList : public Shape
{
private:
    std::vector<ShapePtr> _list;

public:
    ShapeList();
    void add(const ShapePtr &shape);
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const override;
};