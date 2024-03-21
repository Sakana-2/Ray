#include "Material.hpp"

class Specular: public Material{
private:
    Vec3 _albedo;
public:
    Specular(const Vec3& c);
    virtual bool scatter(const Ray& r,const HitRec& hrec, ScatterRec& srec) const override;
};