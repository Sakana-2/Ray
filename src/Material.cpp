#include "Material.hpp"
#include "Matrix.hpp"

Lambertian::Lambertian(const Vec3 &c) : _albedo(c)
{
}

bool Lambertian::scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec, const Vec3 &vup) const
{
    Vec3 target = hrec.p + hrec.n + random_in_unit_sphere();
    // srec.ray = Ray(hrec.p, MakeLocalCo(hrec.n, vup) * random_by_invertion());
    srec.ray = Ray(hrec.p, random_by_invertion());
    // srec.ray = Ray(hrec.p,target - hrec.p);
    srec.albedo = _albedo;
    return true;
}

Metal::Metal(const Vec3 &c) : _albedo(c)
{
}

bool Metal::scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec, const Vec3 &vup) const
{
    Vec3 reflected = reflection(r.direction(), hrec.n);
    srec.ray = Ray(hrec.p, reflected);
    srec.albedo = _albedo;
    return srec.ray.direction().dot(hrec.n) > 0;
}
