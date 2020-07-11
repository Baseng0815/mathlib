#include "../include/Matrix.h"

namespace mathlib {
    Matrix4 createPerspectiveMatrix(double fov)
    {
        return Matrix4::makeIdentity();
    }

    Matrix4 createTransform(const Vector3 &position)
    {
        return Matrix4 {1, 0, 0, position.x(),
            0, 1, 0, position.y(),
            0, 0, 1, position.z(),
            0, 0, 0, 1};
    }

    Matrix4 createRotationX(double angle)
    {
        return Matrix4 {1, 0, 0, 0,
            0, std::cos(angle), -std::sin(angle), 0,
            0, std::sin(angle), std::cos(angle), 0,
            0, 0, 0, 1};
    }

    Matrix4 createRotationY(double angle)
    {
        return Matrix4 {std::cos(angle), 0, std::sin(angle), 0,
            0, 1, 0, 0,
            -std::sin(angle), 0, std::cos(angle), 0,
            0, 0, 0, 1};
    }

    Matrix4 createRotationZ(double angle)
    {
        return Matrix4 {std::cos(angle), -std::sin(angle), 0, 0,
            std::sin(angle), std::cos(angle), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    }

    Matrix3 createTransform(const Vector2 &position)
    {
        return Matrix3 {1, 0, position.x(),
            0, 1, position.y(),
            0, 0, 1};
    }

    Matrix3 createRotation(double angle)
    {
        return Matrix3 {std::cos(angle), -std::sin(angle),
            std::sin(angle), std::cos(angle) };
    }
}
