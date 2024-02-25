#include "ImageFilter.hpp"

GammaFilter::GammaFilter(float factor) : _factor(factor)
{
}

Vec3 GammaFilter::filter(const Vec3 &c) const
{
    return linear_to_gamma(c,_factor);
}
