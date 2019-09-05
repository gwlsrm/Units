#ifndef GEOM_LIB_H_INCLUDED
#define GEOM_LIB_H_INCLUDED

/**@file
    @brief Structures to work with geometry like Point2D, Point3D
*/

/*--------------
 plain (2D)
----------------*/
struct Point2D {
    double x = 0;
    double y = 0;
};

// get line equation coefficients a*x + b*y + c = 0 going through line segment
void line_from_segment(const Point2D& p1, const Point2D& p2, double& a, double& b, double& c);

/*-----------------
 stereo (3D)
-----------------*/
struct Point3D {
    double x = 0;
    double y = 0;
    double z = 0;
};



#endif // GEOM_LIB_H_INCLUDED
