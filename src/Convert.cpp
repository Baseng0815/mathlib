#include "../include/Convert.h"
#include "../include/Constants.h"

namespace mathlib {
    double toRadians(double degrees)
    {
        return degrees * PI / 180.0;
    }

    double toDegrees(double radians)
    {
        return radians * 180.0 / PI;
    }
}
