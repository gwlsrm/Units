#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../datetime.h"

TEST_SUITE("parseDateTime") {
    TEST_CASE("Test parseDateTime") {
        CHECK(
            gwdatetime::parseDateTime("2020-01-01 00:00:00") ==
            gwdatetime::DateTime(std::chrono::seconds(1577836800))
        );
        CHECK(
            gwdatetime::parseDateTime("2020-01-02 02:06:42") ==
            gwdatetime::DateTime(std::chrono::seconds(1577930802))
        );
        CHECK_THROWS(
            gwdatetime::parseDateTime("2020-01-32 02:06:42")
        );
        CHECK_THROWS(
            gwdatetime::parseDateTime("2020-01-02 24:00:00")
        );
        CHECK_THROWS(
            gwdatetime::parseDateTime("2020-01-02 02:60:00")
        );
        CHECK_THROWS(
            gwdatetime::parseDateTime("2020-01-02 02:06:60")
        );
        CHECK_THROWS(
            gwdatetime::parseDateTime("20-01-02 02:06:42")
        );
        CHECK_THROWS(
            gwdatetime::parseDateTime("2020.01.01 00:00:00")
        );
    }
}

TEST_SUITE("toString") {
    TEST_CASE("Test toString") {
        CHECK(
            gwdatetime::toString(gwdatetime::DateTime(std::chrono::seconds(1577836800))) ==
            "2020-01-01 00:00:00"
        );
        CHECK(
            gwdatetime::toString(gwdatetime::DateTime(std::chrono::seconds(1577930802))) ==
            "2020-01-02 02:06:42"
        );
    }
}
