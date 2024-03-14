#include "Material.hpp"

class Lambertian : public Material
{
private:
    Vec3 _albedo;
    Vec3 _emit;
    
public:
    Lambertian(const Vec3 &c,const Vec3 &e);

    virtual bool scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec) const override;
};