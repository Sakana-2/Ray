#pragma once
#include "Vec.hpp"


class Matrix3
{
private:
    Vec3 _a1;
    Vec3 _a2;
    Vec3 _a3;
public:
    Matrix3(const Vec3& a1,const Vec3& a2,const Vec3& a3);
    Vec3 operator*(const Vec3& x) const;
};

inline Matrix3 MakeLocalCo(const Vec3 &n)
{
    Vec3 ex = n.cross(random_another_vec3(n)).normalize();
    Vec3 ez = ex.cross(n).normalize();
    return Matrix3(ex,n,ez);
}
