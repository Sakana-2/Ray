#include "Material.hpp"

class Lambertian : public Material
{
private:
    Vec3 _albedo;

public:
    Lambertian(const Vec3 &c);

    virtual bool scatter(const Ray &r, const HitRec &hrec, ScatterRec &srec) const override;
};