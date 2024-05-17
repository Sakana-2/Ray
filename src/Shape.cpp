#include "Shape.hpp"

std::optional<MaterialPtr> Shape::mat() const
{
    return _material.value();
}

AABB Shape::box() const
{
    return _box;
}

Sphere::Sphere()
{
}

Sphere::Sphere(const Vec3 &c, float r, const MaterialPtr &mat) : _center(c), _radius(r)
{
    _material = mat;
    _box = AABB(Vec3(c[0] - r, c[1] - r, c[2] - r), Vec3(c[0] + r, c[1] + r, c[2] + r));
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
            hrec.mat = _material.value();
            return true;
        }
        temp = (-b + root) / (2.0f * a);
        if (temp < t1 && temp > t0)
        {
            hrec.t = temp;
            hrec.p = r.at(hrec.t);
            hrec.n = (hrec.p - _center) / _radius;
            hrec.mat = _material.value();
            return true;
        }
    }

    return false;
}

Triangle::Triangle()
{
}

Triangle::Triangle(const Vec3 points[3], const MaterialPtr &mat)
    : _points{points[0], points[1], points[2]},
      _n(((points[1] - points[0]).cross(points[2] - points[0])).normalize()),
      _area(std::sqrtf((_points[1] - _points[0]).lengthSqr() * (_points[2] - _points[0]).lengthSqr() - std::powf((_points[1] - _points[0]).dot(_points[2] - _points[0]), 2.0f)) / 2.0f)
{
    _material = mat;
    _box = AABB(min(min(points[0], points[1]), points[2]), max(max(points[0], points[1]), points[2]));
}

float Triangle::area() const
{
    return _area;
}

Vec3 Triangle::sample() const
{
    Vec3 side1 = _points[1] - _points[0];
    Vec3 side2 = _points[2] - _points[0];
    float u, v;
    do
    {
        u = drand48();
        v = drand48();
    } while (!(u >= 0 && v >= 0 && u + v <= 1));

    return _points[0] + u * side1 + v * side2;
}

Vec3 Triangle::n(const Ray &r) const
{
    return _n.dot(r.direction()) < 0 ? _n : -_n;
}

bool Triangle::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    Vec3 e1 = _points[1] - _points[0];
    Vec3 e2 = _points[2] - _points[0];
    Vec3 a2o = r.origin() - _points[0];

    Vec3 d = r.direction();
    const float D = (-d).cross(e1).dot(e2);
    if (D != 0)
    {
        float t = (a2o.cross(e1)).dot(e2) / D;
        float u = ((-d).cross(a2o)).dot(e2) / D;
        float v = ((-d).cross(e1)).dot(a2o) / D;
        if (0 <= u && 0 <= v && u + v <= 1)
        {
            if (t < t1 && t > t0)
            {
                hrec.t = t;
                hrec.p = r.at(t);
                hrec.n = this->n(r);
                hrec.mat = _material.value();
                return true;
            }
        }
    }
    return false;
}

ShapeList::ShapeList()
{
}

void ShapeList::add(const ShapePtr &shape)
{
    _list.push_back(shape);
    
    if (_list.size() == 0)
    {
        _box = shape->box();
    }
    else
    {
        _box = merge(_box, shape->box());
    }
}

bool ShapeList::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
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
