#include "geom_lib.h"

#include <cmath>
#include <cfloat>

#include "math_lib.h"

namespace gwmath {


void lineFromSegment(const Point2D& p1, const Point2D& p2, double& a, double& b, double& c) {
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
    double norm = std::sqrt(a*a + b*b);
    if (isDblZero(norm)) return;
    a /= norm;
    b /= norm;
    c /= norm;
    if (a < -DBL_EPSILON || (std::fabs(a) < DBL_EPSILON && b < -DBL_EPSILON)) {
        a = -a;
        b = -b;
        c = -c;
    }
}

double calcDistance(double x, double y, double z) {
    return std::sqrt(x*x + y*y + z*z);
}

double calcSquareDistance(double x, double y, double z) {
    return x*x + y*y + z*z;
}

double calcSquareDistance(const StaticDoubleVector3& v) {
    return std::pow(v(0,0), 2) + std::pow(v(1,0), 2) + std::pow(v(2,0), 2);
}

void convertCartToSpherical(double x, double y, double z,
    double& r, double& costheta, double& sintheta, double& cosphi, double& sinphi)
{
    r = calcDistance(x, y, z);
    if (!isDblZero(r)) {
        costheta = z / r;
        sintheta = std::sqrt(1.0 - costheta*costheta);
        cosphi = !isDblZero(sintheta) ? x / (r * sintheta) : 1;
        sinphi = !isDblZero(sintheta) ? y / (r * sintheta) : 0;
    } else {
        costheta = 1.0;
        sintheta = 0.0;
        cosphi = 1.0;
        sinphi = 0.0;
    }
}

} // namespace gwmath
