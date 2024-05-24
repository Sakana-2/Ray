#include <cmath>
#include "Analysis.hpp"

bool cramer3(const Matrix3 &A, const Vec3 &b, Vec3 &x)
{

    const float D = A.det();
    if (std::fabsf(D) <= FLT_EPSILON)
    {
        return false;
    }

    x[0] = Matrix3(b, A[1], A[2]).det() / D;
    x[1] = Matrix3(A[0], b, A[2]).det() / D;
    x[2] = Matrix3(A[0], A[1], b).det() / D;
    return true;
}