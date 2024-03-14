#include "ImageFilter.hpp"

GammaFilter::GammaFilter(float factor) : _factor(factor)
{
}

Vec3 GammaFilter::filter(const Vec3 &c) const
{
    return linear_to_gamma(c, _factor);
}

ClampFilter::ClampFilter()
{
}

Vec3 ClampFilter::filter(const Vec3 &c) const
{
    Vec3 dst;
    dst[0] = (c[0] > 1) ? 1 : (c[0] < 0 ? 0 : c[0]);
    dst[1] = (c[1] > 1) ? 1 : (c[1] < 0 ? 0 : c[1]);
    dst[2] = (c[2] > 1) ? 1 : (c[2] < 0 ? 0 : c[2]);
    return dst;
}
