#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "Util.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Shape
{
protected:
    std::optional<MaterialPtr> _material;
public:
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const = 0;
    std::optional<MaterialPtr> mat() const;
};


class Sphere : public Shape
{
private:
    Vec3 _center;
    float _radius;
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
public:
    Plane();
    Plane(const Vec3 &p,const Vec3 &n, const MaterialPtr& mat);
    virtual bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const override;
};

class BoundedPlane : public Shape
{
public:
    virtual float area() const = 0;
    virtual Vec3 sample() const = 0;
    virtual Vec3 n(const Ray &r) const = 0;
};

class Triangle : public BoundedPlane
{
private:
    Vec3 _points[3];
    Vec3 _n;
    float _area;
public:
    Triangle();
    Triangle(const Vec3 points[3], const MaterialPtr& mat);
    virtual float area() const override;
    virtual Vec3 sample() const override;
    virtual Vec3 n(const Ray &r) const override;
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