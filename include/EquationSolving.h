#pragma once

namespace mathlib {
    // return true if solutions exists
    // x0 <= x1 is guaranteed
    bool solveQuadratic(double a, double b, double c, double &x0, double &x1);
}
