#pragma once
#include "Shape.hpp"

struct LightRec
{
    Vec3 xl; //光源内でサンプルした位置
    Vec3 n; //xlでの法線ベクトル
    float pa; //xlを選択する確率密度
    Vec3 emit; //xlからxへの放射輝度
};

//addがただshapelistの型変えただけだからもっと工夫できるかも？
class Lights : public ShapeList
{
private:
    std::vector<std::shared_ptr<Triangle>> _list;
public:
    void add(const std::shared_ptr<Triangle>& shape);
    void sample(const Vec3& x,LightRec &lrec);
    bool hit(const Ray &r, float t0, float t1, HitRec &hrec) const;
};