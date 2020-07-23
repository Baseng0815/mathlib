#pragma once

#include "Matrix.h"

namespace mathlib {
    Matrix4 createOrthoProjection(int left, int right, int top, int bot);
    Matrix4 createPerspectiveProjection(float fov, float aspect, float near, float far);
};
