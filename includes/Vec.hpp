#pragma once
#include <iostream>
#include <cmath>

#include "Util.hpp"

class Vec3
{
private:
	float _data[3];

public:
	Vec3();
	Vec3(float v1);
	Vec3(float v1, float v2, float v3);
	Vec3 operator+(const Vec3 &a) const;
	Vec3 operator+=(const Vec3 &a);
	Vec3 operator-(const Vec3 &a) const;
	Vec3 operator-=(const Vec3 &a);
	Vec3 operator*(float x) const;
	Vec3 operator*(const Vec3 &a) const;
	Vec3 operator*=(float x);
	Vec3 operator*=(const Vec3 &a);
	Vec3 operator/(float x) const;
	Vec3 operator/=(float x);
	float operator[](int i) const;
	float &operator[](int i);
	friend std::ostream &operator<<(std::ostream &os, const Vec3 &a);
	float dot(const Vec3 &a) const;
	Vec3 cross(const Vec3 &a) const;
	Vec3 normalize() const;
	float lengthSqr() const;
};

Vec3 operator*(float a, const Vec3 &v);
bool operator==(const Vec3 &a, const Vec3 &b);
bool operator!=(const Vec3 &a, const Vec3 &b);

inline Vec3 lerp(float t, const Vec3 &a, const Vec3 &b)
{
	return a * (1 - t) + b * t;
}

inline Vec3 random_vec3()
{
	return Vec3(drand48(), drand48(), drand48());
}

inline Vec3 random_in_unit_sphere()
{
	Vec3 p;
	do
	{
		p = 2.f * random_vec3() - Vec3(1.f);
	} while (p.lengthSqr() >= 1.f);
	return p;
}

inline Vec3 random_by_invertion()
{
	Vec3 dst;
	float theta = std::acosf(std::sqrtf(-drand48() + 1));
	float phi = 2 * PI * drand48();

	dst[0] = std::sinf(theta) * std::cosf(phi);
	dst[1] = std::cosf(theta);
	dst[2] = std::sinf(theta) * std::sinf(phi);
	return dst;
}

inline Vec3 reflection(const Vec3 &direction, const Vec3 &normal)
{ // 方向ベクトルは任意の長さでOK,法線ベクトルは正規化済み
	float length = (direction * -1).dot(normal);
	return direction + (normal * (2 * length));
}