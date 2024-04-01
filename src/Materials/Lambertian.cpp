#include "Materials/Lambertian.hpp"
#include "Matrix.hpp"

#define LAMBERT_METHOD 1 //0:棄却法 1:逆関数法

Lambertian::Lambertian(const Vec3 &c,const Vec3 &e) : _albedo(c),_emit(e)
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
    srec.emit = _emit;
    srec.isSpecular = false;
    return true;
}