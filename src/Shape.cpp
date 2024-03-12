#include "Shape.hpp"

Sphere::Sphere()
{
}

Sphere::Sphere(const Vec3 &c, float r, const MaterialPtr& mat) : _center(c), _radius(r), _material(mat)
{
}

bool Sphere::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    Vec3 oc = r.origin() - _center;
    float a = r.direction().dot(r.direction());
    float b = 2.0f * (r.direction().dot(oc));
    float c = oc.dot(oc) - _radius * _radius;
    float D = b * b - 4 * a * c;
    if (D > 0)
    {
        float root = std::sqrtf(D);
        float temp = (-b - root) / (2.0f * a);
        if (temp < t1 && temp > t0)
        {
            hrec.t = temp;
            hrec.p = r.at(hrec.t);
            hrec.n = (hrec.p - _center) / _radius;
            hrec.mat = _material;
            return true;
        }
        temp = (-b + root) / (2.0f * a);
        if (temp < t1 && temp > t0)
        {
            hrec.t = temp;
            hrec.p = r.at(hrec.t);
            hrec.n = (hrec.p - _center) / _radius;
            hrec.mat  = _material;
            return true;
        }
    }

    return false;
}

Plane::Plane()
{
}

Plane::Plane(const Vec3 &p, const Vec3 &n, const MaterialPtr& mat) : _point(p),_n(n),_material(mat)
{
}

bool Plane::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    float D = _n.dot(r.direction());
    if(D != 0)
    {
        float temp = _n.dot(_point-r.origin()) / D;
        if(temp < t1 && temp > t0){
            hrec.t = temp;
            hrec.p = r.at(hrec.t);
            hrec.n = _n;
            hrec.mat = _material;
            return true;
        }
    }
    return false;
}

ShapeList::ShapeList()
{
}

void ShapeList::add(const ShapePtr& shape)
{
    _list.push_back(shape);
}

bool ShapeList::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    HitRec temp_rec;
    bool hit_anything = false;
    float closest_so_far = t1;
    for (auto &p : _list)
    {
        if (p->hit(r,t0,closest_so_far,temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            hrec = temp_rec;
        }
    }
    
    return hit_anything;
}
