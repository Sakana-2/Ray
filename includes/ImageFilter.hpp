#pragma once

#include <cmath>
#include "Vec.hpp"

class ImageFilter
{
public:
    virtual Vec3 filter(const Vec3 &c) const = 0;
};

class GammaFilter : public ImageFilter
{
private:
    float _factor;
public:
    GammaFilter(float factor);
    virtual Vec3 filter(const Vec3 &c) const override;
};

class ClampFilter : public ImageFilter
{
public:
    ClampFilter();
    virtual Vec3 filter(const Vec3 &c) const override;
};

inline Vec3 linear_to_gamma(const Vec3& v,float gammaFactor) {
    float recipGammaFactor = 1.0f / gammaFactor;
    return Vec3(
        std::powf(v[0],recipGammaFactor),
        std::powf(v[1],recipGammaFactor),
        std::powf(v[2],recipGammaFactor));
}

inline Vec3 gamma_tolinear(const Vec3& v, float gammaFactor) {
    return Vec3(
        std::powf(v[0],gammaFactor),
        std::powf(v[1],gammaFactor),
        std::powf(v[2],gammaFactor));
}