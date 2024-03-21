#include "Materials/Specular.hpp"
#include "Matrix.hpp"

Specular::Specular(const Vec3 &c) : _albedo(c)
{
}

bool Specular::scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec) const
{
    Vec3 reflected = reflection(r.direction(), hrec.n);
    srec.ray = Ray(hrec.p, reflected);
    srec.albedo = _albedo;
    return srec.ray.direction().dot(hrec.n) > 0;
}
