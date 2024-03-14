#include "Shape.hpp"

Sphere::Sphere()
{
}

Sphere::Sphere(const Vec3 &c, float r, const MaterialPtr &mat) : _center(c), _radius(r), _material(mat)
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
            hrec.mat = _material;
            return true;
        }
    }

    return false;
}

Plane::Plane()
{
}

Plane::Plane(const Vec3 &p, const Vec3 &n, const MaterialPtr &mat) : _point(p), _n(n), _material(mat)
{
}

bool Plane::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    float D = _n.dot(r.direction());
    if (D != 0)
    {
        float temp = _n.dot(_point - r.origin()) / D;
        if (temp < t1 && temp > t0)
        {
            hrec.t = temp;
            hrec.p = r.at(hrec.t);
            hrec.n = _n;
            hrec.mat = _material;
            return true;
        }
    }
    return false;
}

Triangle::Triangle()
{
}

Triangle::Triangle(const Vec3 points[3], const MaterialPtr &mat) : _points{points[0], points[1], points[2]}, _material(mat)
{
}

bool Triangle::hit(const Ray &r, float t0, float t1, HitRec &hrec) const
{
    Vec3 a = _points[0];
    Vec3 b = _points[1];
    Vec3 c = _points[2];

    Vec3 normal = (b - a).cross(c - a).normalize(); // 平面の法線ベクトル

    const float d = r.direction().dot(normal);
    if (d != 0)
    {
        const float param = (a - r.origin()).dot(normal) / d; // (a.dot(normal) - r.origin().dot(normal)) / d;

        Vec3 crossing = r.at(param);

        float d2, d3, alpha, beta, gamma;
        if (((d2 = b[1] * (a[0] - c[0]) + b[0] * (-a[1] + c[1]) - a[0] * c[1] + a[1] * c[0]) != 0) &&
            ((d3 = a[1] * (b[0] - c[0]) - a[0] * (b[1] - c[1]) - b[0] * c[1] + b[1] * c[0]) != 0))
        {
            alpha = (b[1] * (crossing[0] - c[0]) + b[0] * (c[1] - crossing[1]) + crossing[1] * c[0] - crossing[0] * c[1]) / d2;
            beta = (a[1] * (crossing[0] - c[0]) - a[0] * (crossing[1] - c[1]) + c[0] * crossing[1] - c[1] * crossing[0]) / d3;
            gamma = 1 - alpha - beta;
        }
        else if (
            ((d2 = c[1] * (a[0] - b[0]) + c[0] * (-a[1] + b[1]) - a[0] * b[1] + a[1] * b[0]) != 0) &&
            ((d3 = a[1] * (c[0] - b[0]) - a[0] * (c[1] - b[1]) - c[0] * b[1] + c[1] * b[0]) != 0))
        {
            alpha = (c[1] * (crossing[0] - b[0]) + c[0] * (b[1] - crossing[2]) + crossing[2] * b[0] - crossing[0] * b[1]) / d2;
            gamma = (a[1] * (crossing[0] - b[0]) - a[0] * (crossing[2] - b[1]) + b[0] * crossing[2] - b[1] * crossing[0]) / d3;
            beta = 1 - alpha - gamma;
        }
        else if (
            ((d2 = c[1] * (b[0] - a[0]) + c[0] * (-b[1] + a[1]) - b[0] * a[1] + b[1] * a[0]) != 0) &&
            ((d3 = b[1] * (c[0] - a[0]) - b[0] * (c[1] - a[1]) - c[0] * a[1] + c[1] * a[0]) != 0))
        {
            beta = (c[1] * (crossing[1] - a[0]) + c[0] * (a[1] - crossing[2]) + crossing[2] * a[0] - crossing[1] * a[1]) / d2;
            gamma = (b[1] * (crossing[1] - a[0]) - b[0] * (crossing[2] - a[1]) + a[0] * crossing[2] - a[1] * crossing[1]) / d3;
            alpha = 1 - beta - gamma;
        }
        else
        {
            return false;
        }

        if (0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1)
        {
            // std::cout << param << " " << t1 << " " << t0 << std::endl;
            if (param < t1 && param > t0)
            {
                hrec.t = param;
                hrec.p = crossing;
                hrec.n = normal;
                hrec.mat = _material;
                // std::cout << hrec.t << std::endl;
                // std::cout << hrec.p << std::endl;
                // std::cout << hrec.n << std::endl;
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
