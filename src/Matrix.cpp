#include "Matrix.hpp"

Matrix3::Matrix3(const Vec3 &a1, const Vec3 &a2, const Vec3 &a3): _a1(a1), _a2(a2), _a3(a3)
{
}

Vec3 Matrix3::operator*(const Vec3 &x) const
{
    Vec3 dst;
    dst[0] = Vec3(_a1[0],_a2[0],_a3[0]).dot(x);
    dst[1] = Vec3(_a1[1],_a2[1],_a3[1]).dot(x);
    dst[2] = Vec3(_a1[2],_a2[2],_a3[2]).dot(x);
    return dst;
}