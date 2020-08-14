#include "../include/MatrixTransform.h"

#include "../include/Convert.h"

namespace mathlib {
    Matrix4 createPerspectiveProjection(float fov, float aspect, float clipNear, float clipFar)
    {
        // x' = x / -z
        // y' = y / -z
        // z = -z / -z = 1
        // top = tan(fov / 2) * clipNear
        // bot = -top
        // right = top * aspect
        // left = -top * aspect

        float t = std::tan(toRadians(fov / 2.0f)) * clipNear;
        float b = -t;
        float r = t * aspect;
        float l = -r;

        return Matrix4
        {
            2.f * clipNear / (r - l), 0.f, (r + l) / (r - l), 0.f,
            0.f, 2.f * clipNear / (t - b), (t + b) / (t - b), 0.f,
            0.f, 0.f, -(clipFar + clipNear) / (clipFar - clipNear), - 2.f * clipFar * clipNear / (clipFar - clipNear),
            0.f, 0.f, -1.f, 0.f
        };
    }

    Matrix4 createOrthographicProjection(float left, float right, float top, float bot, float clipNear, float clipFar)
    {
        return Matrix4
        {
            2.f / (right - left), 0.f, 0.f, -(right + left) / (right - left),
            0.f, 2.f / (top - bot), 0.f, -(top + bot) / (top - bot),
            0.f, 0.f, -2.f / (clipFar - clipNear), -(clipFar + clipNear) / (clipFar - clipNear),
            0.f, 0.f, 0.f, 1.f
        };
    }

    Matrix4 createOrthographicProjection(float left, float right, float top, float bot)
    {
        return Matrix4
        {
            2.f / (right - left), 0.f, 0.f, -(right + left) / (right - left),
            0.f, 2.f / (top - bot), 0.f, -(top + bot) / (top - bot),
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
    }

    Matrix4 createViewMatrix(const Vector3 &position, const Vector3 &front, const Vector3 &up)
    {

    }

    Matrix4 createTranslation(const Vector3 &position)
    {
        return Matrix4 {1.0f, 0.0f, 0.0f, position.x(),
            0.0f, 1.0f, 0.0f, position.y(),
            0.0f, 0.0f, 1.0f, position.z(),
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix3 createTranslation(const Vector2 &position)
    {
        return Matrix3 {1.0f, 0.0f, position.x(),
            0.0f, 1.0f, position.y(),
            0.0f, 0.0f, 1.0f
        };
    }

    Matrix4 createRotationX(float angle)
    {
        return Matrix4 {1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, std::cos(angle), -std::sin(angle), 0.0f,
            0.0f, std::sin(angle), std::cos(angle), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix4 createRotationY(float angle)
    {
        return Matrix4 {std::cos(angle), 0.0f, std::sin(angle), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -std::sin(angle), 0.0f, std::cos(angle), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix4 createRotationZ(float angle)
    {
        return Matrix4 {std::cos(angle), -std::sin(angle), 0.0f, 0.0f,
            std::sin(angle), std::cos(angle), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix3 createRotation(float angle)
    {
        return Matrix3 {std::cos(angle), -std::sin(angle),
            std::sin(angle), std::cos(angle) };
    }

    Matrix4 createScale(const Vector3 &scale)
    {
        return Matrix4 {
            scale.x(), 0.0f, 0.0f, 0.0f,
            0.0f, scale.y(), 0.0f, 0.0f,
            0.0f, 0.0f, scale.z(), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
}
