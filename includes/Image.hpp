#pragma once
#include <vector>

#include "Vec.hpp"
#include "ImageFilter.hpp"

struct rgb
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class Image
{
private:
    std::vector<rgb> _pixels;
    unsigned int _width;
    unsigned int _height;
    std::vector<std::unique_ptr<ImageFilter>> _filters;
public:
    Image(unsigned int height, unsigned int width);
    unsigned int width() const;
    unsigned int height() const;
    rgb *data();
    rgb get_pixel(int j, int i) const;
    void set_pixel(int j, int i, const Vec3& data);
};
