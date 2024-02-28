#include "Material.hpp"
#include "Matrix.hpp"

#define LAMBERT_METHOD 1 //0:棄却法 1:逆関数法

Lambertian::Lambertian(const Vec3 &c) : _albedo(c)
{
}

bool Lambertian::scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec) const
{
    #if LAMBERT_METHOD == 0
    Vec3 target = hrec.p + hrec.n + random_in_unit_sphere();
    srec.ray = Ray(hrec.p,target - hrec.p);
    #elif LAMBERT_METHOD == 1
    srec.ray = Ray(hrec.p, MakeLocalCo(hrec.n) * random_by_invertion());
    #endif
    srec.albedo = _albedo;
    return true;
}

Metal::Metal(const Vec3 &c) : _albedo(c)
{
}

bool Metal::scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec) const
{
    Vec3 reflected = reflection(r.direction(), hrec.n);
    srec.ray = Ray(hrec.p, reflected);
    srec.albedo = _albedo;
    return srec.ray.direction().dot(hrec.n) > 0;
}
