#include "Material.hpp"

class Metal: public Material{
private:
    Vec3 _albedo;
public:
    Metal(const Vec3& c);
    virtual bool scatter(const Ray& r,const HitRec& hrec, ScatterRec& srec) const override;
};