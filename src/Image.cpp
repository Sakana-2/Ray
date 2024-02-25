#include "Image.hpp"

Image::Image(unsigned int height, unsigned int width) : _width(width), _height(height), _pixels(std::vector<rgb>(width * height)){
    _filters.push_back(std::make_unique<GammaFilter>(GAMMA_FACTOR));
};

unsigned int Image::width() const
{
    return _width;
}

unsigned int Image::height() const
{
    return _height;
}

rgb *Image::data()
{
    return _pixels.data();
}

rgb Image::get_pixel(int j, int i) const
{
    return _pixels[j * _width + i];
}

void Image::set_pixel(int j, int i, const Vec3 &data)
{
    Vec3 c(data);
    for (auto &&f : _filters)
    {
        c = f->filter(c);
    }
    
    rgb pix = {static_cast<unsigned char>(c[0] * 255.99f), static_cast<unsigned char>(c[1] * 255.99f), static_cast<unsigned char>(c[2] * 255.99f)};
    // _pixels[j * _width + i] = pix;
    _pixels[(_height - j - 1) * _width + i] = pix;
}