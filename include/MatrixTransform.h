#pragma once

#include "Matrix.h"

namespace mathlib {
    Matrix4 createPerspectiveMatrix(double fov);
    Matrix4 createTransform(const Vector3 &position);
    Matrix3 createTransform(const Vector2 &position);
    Matrix4 createRotationX(double angle);
    Matrix4 createRotationY(double angle);
    Matrix4 createRotationZ(double angle);
    Matrix3 createRotation(double angle);
}
