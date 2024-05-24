#pragma once
#include <cmath>
#include "Vec.hpp"

class Matrix3
{
private:
    Vec3 _a[3];

public:
    Matrix3(const Vec3 &a1, const Vec3 &a2, const Vec3 &a3);
    Vec3 operator*(const Vec3 &x) const;
    Vec3 operator[](int i) const;
    Vec3 &operator[](int i);
    float det() const;
};

inline Matrix3 MakeLocalCo(const Vec3 &n)
{

    Vec3 x(1, 0, 0), y(0, 1, 0);
    Vec3 another_vec;
    float dot_x = std::fabsf(x.dot(n));
    float dot_y = std::fabsf(y.dot(n));
    if (dot_x < dot_y)
    {
        another_vec = x;
    }
    else
    {
        another_vec = y;
    }
    Vec3 ex = n.cross(another_vec).normalize();
    Vec3 ez = ex.cross(n).normalize();
    return Matrix3(ex, n, ez);
}
