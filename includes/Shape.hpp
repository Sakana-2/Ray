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

class Plane : public Shape
{
private:
    Vec3 _point;
    Vec3 _n;
    MaterialPtr _material;
public:
    Plane();
    Plane(const Vec3 &p,const Vec3 &n, const MaterialPtr& mat);
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const override;
};

class Triangle : public Shape
{
private:
    Vec3 _points[3];
    MaterialPtr _material;
public:
    Triangle();
    Triangle(const Vec3 points[3], const MaterialPtr& mat);
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