#pragma once
#ifndef GEOM_LIB_H_INCLUDED
#define GEOM_LIB_H_INCLUDED

/**@file
    @brief Structures to work with geometry like Point2D, Point3D
*/

#include <iostream>
#include <utility>
#include <vector>

#include "gw_static_matrix.h"

namespace gwmath{

/*--------------
 plain (2D)
----------------*/
struct Point2d {
    double x = 0;
    double y = 0;
    static Point2d fromPair(const std::pair<double, double>& point);
    friend Point2d operator-(const Point2d& point);
    friend bool operator==(const Point2d& lhs, const Point2d& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Point2d& point);
};
using Vector2d = Point2d;
using Polygon = std::vector<Point2d>;
Polygon polygonFromPairs(const std::vector<std::pair<double, double>>& polygon);

// get line equation coefficients a*x + b*y + c = 0 going through line segment
void lineFromSegment(const Point2d& p1, const Point2d& p2, double& a, double& b, double& c);
// is polygon convex
bool isConvexPolygon(const Polygon& vertices);
// check if point (0, 0) in the convex polygon
bool pointInConvexPolygonOrigin(const Polygon& v);


/*-----------------
 stereo (3D)
-----------------*/
struct Point3D {
    double x = 0;
    double y = 0;
    double z = 0;
};

// calculate Euclidean distance
double calcDistance(double x, double y, double z);

// calulates square of euclidian distance
double calcSquareDistance(double x, double y, double z);
double calcSquareDistance(const StaticDoubleVector3& v);

// Convert cartesian coordinates to spherical
void convertCartToSpherical(double x, double y, double z,
    double& r, double& costheta, double& sintheta, double& cosphi, double& sinphi);


// Create rotation matrix around x-axis
StaticDoubleMatrix3x3 createXRotationMatrix(double cosphi, double sinphi);
// Create rotation matrix around y-axis
StaticDoubleMatrix3x3 createYRotationMatrix(double costheta, double sintheta);
// Create rotation matrix around z-axis
StaticDoubleMatrix3x3 createZRotationMatrix(double cospsi, double sinpsi);

// Create rotation matrix around x-axis
StaticDoubleMatrix3x3 createXMinusRotationMatrix(double cosphi, double sinphi);
// Create rotation matrix around y-axis
StaticDoubleMatrix3x3 createYMinusRotationMatrix(double costheta, double sintheta);
// Create rotation matrix around z-axis
StaticDoubleMatrix3x3 createZMinusRotationMatrix(double cospsi, double sinpsi);


} // namespace gwmath

#endif // GEOM_LIB_H_INCLUDED
