#include "../include/EquationSolving.h"

#include <cmath>
#include <algorithm>

namespace mathlib {
    bool solveQuadratic(double a, double b, double c, double &x0, double &x1)
    {
        float discr = b * b - 4 * a * c;
        if (discr < 0) {
            return false;
        } else if (discr == 0) {
            x0 = x1 = -0.5 * b / a;
        } else {
            float q = (b > 0)?
                -0.5 * (b + std::sqrt(discr)) :
                -0.5 * (b - std::sqrt(discr));
            x0 = q / a;
            x1 = c / q;
        }

        if (x0 > x1) {
            std::swap(x0, x1);
        }

        return true;
    }
}
