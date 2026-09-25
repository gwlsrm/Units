#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "geom_lib.h"

using namespace std;
using namespace gwmath;

TEST_SUITE("geom2d_test_suite") {

    TEST_CASE("test_point2d_constructor") {
        Point2d p = Point2d::fromPair(std::pair<double, double>{1.0, 2.0});
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
    }

    TEST_CASE("test_point2d_operator-") {
        CHECK(-Point2d{1.5, 2.3} == Point2d{-1.5, -2.3});
        CHECK(-Point2d{-1.5, 2.3} == Point2d{1.5, -2.3});
        CHECK(-Point2d{1.5, -2.3} == Point2d{-1.5, 2.3});
        CHECK(-Point2d{-1.5, -2.3} == Point2d{1.5, 2.3});
    }

    TEST_CASE("test_is_convex_polygon") {
        // square
        CHECK(isConvexPolygon({
            {0.0, 0.0},
            {0.0, 1.0},
            {1.0, 1.0},
            {1.0, 0.0},
        }));
        // 4-angles, not convex
        CHECK(!isConvexPolygon({
            {0.0, 0.0},
            {0.5, 1.0},
            {1.0, 0.0},
            {0.5, 0.5},
        }));
    }

    TEST_CASE("test_origin_in_polygon") {
        CHECK(pointInConvexPolygonOrigin({
            {-0.5, -0.5},
            {-0.5, 0.5},
            {0.5, 0.5},
            {0.5, -0.5},
        }));
        CHECK(pointInConvexPolygonOrigin({
            {0.5, 0.5},
            {0.5, 1.5},
            {1.5, 1.5},
            {1.5, 0.5},
        }) == false);
        CHECK(pointInConvexPolygonOrigin({
            {-0.5, 0.5},
            {-0.5, 1.5},
            {0.5, 1.5},
            {0.5, 0.5},
        }) == false);
        CHECK(pointInConvexPolygonOrigin({
            {0.5, -0.5},
            {0.5, 0.5},
            {1.5, 0.5},
            {1.5, -0.5},
        }) == false);

    }

}
