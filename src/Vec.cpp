#include <cmath>

#include "Vec.hpp"

Vec3::Vec3() : _data{0, 0, 0} {}

Vec3::Vec3(float v1) : _data{v1, v1, v1} {}

Vec3::Vec3(float v1, float v2, float v3) : _data{v1, v2, v3}
{
}

Vec3 Vec3::operator+(const Vec3 &a) const
{
	Vec3 dst;
	dst[0] = this->_data[0] + a[0];
	dst[1] = this->_data[1] + a[1];
	dst[2] = this->_data[2] + a[2];
	return dst;
}

Vec3 Vec3::operator+=(const Vec3 &a)
{
	this->_data[0] += a[0];
	this->_data[1] += a[1];
	this->_data[2] += a[2];
	return *this;
}

Vec3 Vec3::operator-(const Vec3 &a) const
{
	Vec3 dst;
	dst[0] = this->_data[0] - a[0];
	dst[1] = this->_data[1] - a[1];
	dst[2] = this->_data[2] - a[2];
	return dst;
}

Vec3 Vec3::operator-=(const Vec3 &a)
{
	this->_data[0] -= a[0];
	this->_data[1] -= a[1];
	this->_data[2] -= a[2];
	return *this;
}

Vec3 Vec3::operator*(float x) const
{
	Vec3 dst;
	dst[0] = this->_data[0] * x;
	dst[1] = this->_data[1] * x;
	dst[2] = this->_data[2] * x;
	return dst;
}

Vec3 Vec3::operator*(const Vec3 &a) const
{
	Vec3 dst;
	dst[0] = this->_data[0] * a[0];
	dst[1] = this->_data[1] * a[1];
	dst[2] = this->_data[2] * a[2];
    return dst;
}

Vec3 Vec3::operator*=(float x)
{
	this->_data[0] *= x;
	this->_data[1] *= x;
	this->_data[2] *= x;
	return *this;
}

Vec3 Vec3::operator*=(const Vec3 &a)
{
	this->_data[0] *= a[0];
	this->_data[1] *= a[1];
	this->_data[2] *= a[2];
	return *this;
}

Vec3 Vec3::operator/(float x) const
{
	Vec3 dst;
	dst[0] = this->_data[0] / x;
	dst[1] = this->_data[1] / x;
	dst[2] = this->_data[2] / x;
	return dst;
}

Vec3 Vec3::operator/=(float x)
{
	this->_data[0] /= x;
	this->_data[1] /= x;
	this->_data[2] /= x;
	return *this;
}

float Vec3::operator[](int i) const
{
	return _data[i];
}

float &Vec3::operator[](int i)
{
	return _data[i];
}

float Vec3::dot(const Vec3 &a) const
{
	return this->_data[0] * a[0] + this->_data[1] * a[1] + this->_data[2] * a[2];
}

Vec3 Vec3::cross(const Vec3 &a) const
{
	Vec3 dst(0, 0, 0);
	dst[0] = this->_data[1] * a[2] - this->_data[2] * a[1];
	dst[1] = this->_data[2] * a[0] - this->_data[0] * a[2];
	dst[2] = this->_data[0] * a[1] - this->_data[1] * a[0];
	return dst;
}

std::ostream &operator<<(std::ostream &os, const Vec3 &a)
{
	os << a[0] << " " << a[1] << " " << a[2];
	return os;
}

Vec3 Vec3::normalize() const
{
	Vec3 dst;
	float length = std::sqrt(this->_data[0] * this->_data[0] + this->_data[1] * this->_data[1] + this->_data[2] * this->_data[2]);
	if (length != 0)
	{
		dst[0] = this->_data[0] / length;
		dst[1] = this->_data[1] / length;
		dst[2] = this->_data[2] / length;
	}
	return dst;
}

float Vec3::lengthSqr() const
{
	return this->_data[0] * this->_data[0] + this->_data[1] * this->_data[1] + this->_data[2] * this->_data[2];
}

Vec3 operator*(float a, const Vec3 &v)
{
	return Vec3(a * v[0], a * v[1], a * v[2]);
}