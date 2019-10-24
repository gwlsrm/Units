#define BOOST_TEST_MODULE str_test_module
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

//#include "str_utils.h"
#include "../StringUnits/str_utils.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ip_test_suite)

BOOST_AUTO_TEST_CASE(test_str_trim) {
    string expected = "test string";
    BOOST_TEST(trim("   test string   ") == expected);
    BOOST_TEST(trim("   test string") == expected);
    BOOST_TEST(trim("test string   ") == expected);
    BOOST_TEST(trim("test string") == expected);
    BOOST_TEST(trim(" ") == ""s);
    BOOST_TEST(trim("\n") == ""s);
}

BOOST_AUTO_TEST_CASE(test_str_trim_right) {
        BOOST_TEST(trim_right("   test string   ") == "   test string"sv);
        BOOST_TEST(trim_right("   test string") == "   test string"sv);
        BOOST_TEST(trim_right("test string   ") == "test string"sv);
        BOOST_TEST(trim_right("test string") == "test string"sv);
        BOOST_TEST(trim_right(" ") == ""s);
        BOOST_TEST(trim_right("\n") == ""s);
}

BOOST_AUTO_TEST_CASE(test_tolower) {
    BOOST_TEST(str_tolower("Test string") == "test string"sv);
    BOOST_TEST(str_tolower("TesT StrIng") == "test string"sv);
    BOOST_TEST(str_tolower("test string") == "test string"sv);
}

BOOST_AUTO_TEST_CASE(test_startsWith) {
    BOOST_TEST(startWith("Test string", "Test"));
    BOOST_TEST(startWith("Test string"s, "Test"s));
    BOOST_TEST(startWith("  Test string"s, "  Test"s));
    BOOST_TEST(startWith("  Test"s, "  Test"s));
    BOOST_TEST(startWith("  Test string"s, "  Test "s));
    BOOST_TEST(startWith("  Test string", "  Test "));
}

BOOST_AUTO_TEST_CASE(test_join_strings) {
    BOOST_TEST(join_strings({"str1", "str2", "str3"}) == "str1 str2 str3"sv);
    BOOST_TEST(join_strings({"str1", "str2", "str3"}, ',') == "str1,str2,str3"sv);
    const vector<string> si {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    BOOST_TEST(
        join_strings({"-" + si[5], "-" + si[10], si[2], "(", si[9], ":", si[4], ")"}) ==
        "-" + si[5] + " -" + si[10] + " " + si[2] + " ( " + si[9] + " : " + si[4] + " )"
    );
}


BOOST_AUTO_TEST_SUITE_END()