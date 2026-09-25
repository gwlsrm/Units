#include "geom_lib.h"

#include <cfloat>
#include <cmath>

#include "math_lib.h"

namespace gwmath {

constexpr double EPS = 1e-9;


// ************** 2d geometry ***************

Point2d Point2d::fromPair(const std::pair<double, double>& point) {
    return {point.first, point.second};
}

bool operator==(const Point2d& lhs, const Point2d& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Point2d operator-(const Point2d& point) {
    return {-point.x, -point.y};
}

std::ostream& operator<<(std::ostream& out, const Point2d& point) {
    out << "{" << point.x << "," << point.y << "}";
    return out;
}

Polygon polygonFromPairs(const std::vector<std::pair<double, double>>& polygon) {
    Polygon res;
    res.reserve(polygon.size());
    for (const auto& point : polygon) {
        res.emplace_back(Point2d::fromPair(point));
    }
    return res;
}

void lineFromSegment(const Point2d& p1, const Point2d& p2, double& a, double& b, double& c) {
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

namespace {

Vector2d operator-(const Point2d& a, const Point2d& b) {
    return {a.x - b.x, a.y - b.y};
}

// cross calculates cross product of 2 vectors and returns z-component
// it can be used to find the direction of rotation
double cross(const Vector2d& a, const Vector2d& b) {
    return a.x * b.y - a.y * b.x;
}

}


bool isConvexPolygon(const Polygon& vertices) {
    int n = (int)vertices.size();
    if (n < 3) return false;

    int direction = 0; // 1 — turn left, -1 — turn right

    for (int i = 0; i < n; ++i) {
        const Point2d& a = vertices[i];
        const Point2d& b = vertices[(i + 1) % n];
        const Point2d& c = vertices[(i + 2) % n];

        Vector2d ab = b - a;
        Vector2d bc = c - b;

        double cr = cross(ab, bc);

        // skip 3 points on one line (is it correct?)
        if (std::fabs(cr) < EPS)
            continue;

        int currentDirection = (cr > 0) ? 1 : -1;

        if (direction == 0) {
            direction = currentDirection;
        } else if (direction != currentDirection) {
            return false; // turn to another direction
        }
    }

    if (direction == 0) {
        throw std::runtime_error("all vertices are collinear! it is not a polygon");
    }
    return true;
}

bool pointInConvexPolygonOrigin(const Polygon& v) {
    int n = v.size();
    int sign = 0;

    for (int i = 0; i < n; ++i) {
        Point2d a = v[i];
        Point2d b = v[(i + 1) % n];

        double cr = cross(b - a, -a);

        // point (0, 0) lies on edge line
        if (fabs(cr) < EPS) {
            return false;
        }

        int s = cr > 0 ? 1 : -1;
        if (sign == 0) {
            sign = s;
        } else if (sign != s) {
            return false;
        }
    }

    return true;
}


// ************** 3d geometry ***************
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


StaticDoubleMatrix3x3 createXRotationMatrix(double cosphi, double sinphi) {
    return gwmath::StaticDoubleMatrix3x3{
        {1, 0,       0     },
        {0, cosphi, -sinphi},
        {0, sinphi,  cosphi},
    };
}


StaticDoubleMatrix3x3 createYRotationMatrix(double costheta, double sintheta) {
    return gwmath::StaticDoubleMatrix3x3{
        { costheta, 0, sintheta},
        { 0,        1, 0     },
        {-sintheta, 0, costheta},
    };
}


StaticDoubleMatrix3x3 createZRotationMatrix(double cospsi, double sinpsi) {
    return gwmath::StaticDoubleMatrix3x3{
        {cospsi, -sinpsi, 0},
        {sinpsi,  cospsi, 0},
        {0,       0,      1},
    };
}


StaticDoubleMatrix3x3 createXMinusRotationMatrix(double cosphi, double sinphi) {
    return gwmath::StaticDoubleMatrix3x3{
        {1,  0,      0     },
        {0,  cosphi, sinphi},
        {0, -sinphi, cosphi},
    };
}


StaticDoubleMatrix3x3 createYMinusRotationMatrix(double costheta, double sintheta) {
    return gwmath::StaticDoubleMatrix3x3{
        {costheta, 0, -sintheta},
        {0,        1,  0     },
        {sintheta, 0,  costheta},
    };
}


StaticDoubleMatrix3x3 createZMinusRotationMatrix(double cospsi, double sinpsi) {
    return gwmath::StaticDoubleMatrix3x3{
        { cospsi, sinpsi, 0},
        {-sinpsi, cospsi, 0},
        { 0,      0,      1},
    };
}


} // namespace gwmath
