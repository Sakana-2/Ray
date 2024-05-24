#include "Matrix.hpp"

Matrix3::Matrix3(const Vec3 &a1, const Vec3 &a2, const Vec3 &a3)
{
    _a[0] = a1;
    _a[1] = a2;
    _a[2] = a3;
}

Vec3 Matrix3::operator*(const Vec3 &x) const
{
    Vec3 dst;
    dst[0] = Vec3(_a[0][0],_a[1][0],_a[2][0]).dot(x);
    dst[1] = Vec3(_a[0][1],_a[1][1],_a[2][1]).dot(x);
    dst[2] = Vec3(_a[0][2],_a[1][2],_a[2][2]).dot(x);
    return dst;
}

Vec3 Matrix3::operator[](int i) const
{
    return _a[i];
}

Vec3 &Matrix3::operator[](int i)
{
    return _a[i];
}

float Matrix3::det() const
{
    return (_a[0]).cross(_a[1]).dot(_a[2]); //枢軸要素の積との速度の比較行う
}
