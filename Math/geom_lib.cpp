// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "geom_lib.h"

#include <cmath>
#include <cfloat>

#include "math_lib.h"

using namespace std;


void line_from_segment(const Point2D& p1, const Point2D& p2, double& a, double& b, double& c) {
    /// get line equation coefficients a*x + b*y + c = 0 going through line segment
    /*solution is:
        a = p1y - P2y
        b = p2x - p1x
        c = -a*p1x - b*p1y
        coeff norm is a^2 + b^2 = 1. divide to sqrt(a^2 + b^2)
        if a < -epsilon or abs(a) < epsilon and B < -epsilon, so multiply on -1
    */
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a*p1.x - b*p1.y;
    double norm = sqrt(a*a + b*b);
    if (isDblZero(norm)) return;
    a /= norm;
    b /= norm;
    c /= norm;
    if (a < -DBL_EPSILON || (fabs(a) < DBL_EPSILON && b < -DBL_EPSILON)) {
        a = -a;
        b = -b;
        c = -c;
    }
}
