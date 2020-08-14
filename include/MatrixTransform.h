#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace mathlib {
    Matrix4 createPerspectiveProjection(float fov, float aspect, float clipNear, float clipFar);
    Matrix4 createOrthographicProjection(float left, float right, float top, float bot, float clipNear, float clipFar);
    Matrix4 createOrthographicProjection(float left, float right, float top, float bot);
    Matrix4 createViewMatrix(const Vector3 &position, const Vector3 &front, const Vector3 &up);
    Matrix4 createTranslation(const Vector3 &position);
    Matrix3 createTranslation(const Vector2 &position);
    Matrix4 createRotationX(float angle);
    Matrix4 createRotationY(float angle);
    Matrix4 createRotationZ(float angle);
    Matrix3 createRotation(float angle);
    Matrix4 createScale(const Vector3 &scale);
}
