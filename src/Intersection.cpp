#include <string.h>
#include <iostream>

#include "Intersection.hpp"

bool intersection(const Vec3& start, const Vec3& direction, const Vec3 triangle[3])
{
	Vec3 a = triangle[0];
	Vec3 b = triangle[1];
	Vec3 c = triangle[2];

	Vec3 normal = (b - a).cross(c - a); //平面の法線ベクトル
	
	double d = direction.dot(normal);
	if (d == 0)
	{
		return false;
	}

	double param = (a.dot(normal) - start.dot(normal)) / d;

	Vec3 crossing = start + direction * param;

	double d2, d3, alpha, beta, gamma;
	if (((d2 = b[1] * (a[0] - c[0]) + b[0] * (-a[1] + c[1]) - a[0] * c[1] + a[1] * c[0]) != 0) &&
		((d3 = a[1] * (b[0] - c[0]) - a[0] * (b[1] - c[1]) - b[0] * c[1] + b[1] * c[0]) != 0))
	{
		alpha = (b[1] * (crossing[0] - c[0]) + b[0] * (c[1] - crossing[1]) + crossing[1] * c[0] - crossing[0] * c[1]) / d2;
		beta = (a[1] * (crossing[0] - c[0]) - a[0] * (crossing[1] - c[1]) + c[0] * crossing[1] - c[1] * crossing[0]) / d3;
		gamma = 1 - alpha - beta;
	}
	else if (
		((d2 = c[1] * (a[0] - b[0]) + c[0] * (-a[1] + b[1]) - a[0] * b[1] + a[1] * b[0]) != 0) &&
		((d3 = a[1] * (c[0] - b[0]) - a[0] * (c[1] - b[1]) - c[0] * b[1] + c[1] * b[0]) != 0))
	{
		alpha = (c[1] * (crossing[0] - b[0]) + c[0] * (b[1] - crossing[2]) + crossing[2] * b[0] - crossing[0] * b[1]) / d2;
		gamma = (a[1] * (crossing[0] - b[0]) - a[0] * (crossing[2] - b[1]) + b[0] * crossing[2] - b[1] * crossing[0]) / d3;
		beta = 1 - alpha - gamma;
	}
	else if (
		((d2 = c[1] * (b[0] - a[0]) + c[0] * (-b[1] + a[1]) - b[0] * a[1] + b[1] * a[0]) != 0) &&
		((d3 = b[1] * (c[0] - a[0]) - b[0] * (c[1] - a[1]) - c[0] * a[1] + c[1] * a[0]) != 0))
	{
		beta = (c[1] * (crossing[1] - a[0]) + c[0] * (a[1] - crossing[2]) + crossing[2] * a[0] - crossing[1] * a[1]) / d2;
		gamma = (b[1] * (crossing[1] - a[0]) - b[0] * (crossing[2] - a[1]) + a[0] * crossing[2] - a[1] * crossing[1]) / d3;
		alpha = 1 - beta - gamma;
	}
	else
	{
		return false;
	}

	if (0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}