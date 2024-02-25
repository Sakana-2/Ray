#include <cmath>

#include "Camera.hpp"
#include "Util.hpp"

Camera::Camera(){}

Camera::Camera(const Vec3& u,const Vec3& v,const Vec3& w):_uvw{u,v,w},_origin(Vec3(0)){}

Camera::Camera(const Vec3& lookfrom,const Vec3& lookat,const Vec3& vup, float vfov, float aspect)
{
    Vec3 u, v, w;
    float halfH = std::tanf(radian(vfov) / 2.0f);
    float halfW = aspect * halfH;
    _origin = lookfrom;

    w = lookfrom - lookat;
    w.normalize();
    u = vup.cross(w);
    u.normalize();
    v = w.cross(u);

    _uvw[0] = u * 2.0f * halfW;
    _uvw[1] = v * 2.0f * halfH;
    _uvw[2] = _origin - u * halfW - v * halfH - w;
}

Ray Camera::emitRay(float u,float v){
    return Ray(_origin,_uvw[2]+_uvw[0] * u+_uvw[1] * v - _origin);
}