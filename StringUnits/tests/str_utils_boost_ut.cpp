#define BOOST_TEST_MODULE str_test_module
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

#include "str_utils.h"
#include "fileutils.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(str_test_suite)

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

    BOOST_AUTO_TEST_CASE(test_split_into_words) {
        {
            string str = "a1 a2 a3";
            auto res = split_into_words(str);
            vector<string> expected = {"a1", "a2", "a3"};
            BOOST_TEST(res == expected);
        }
        {
            string str = " a1 a2 a3";
            auto res = split_into_words(str);
            vector<string> expected = {"a1", "a2", "a3"};
            BOOST_TEST(res == expected);
        }
        {
            string str = "a1 a2 a3 ";
            auto res = split_into_words(str);
            vector<string> expected = {"a1", "a2", "a3"};
            BOOST_TEST(res == expected);
        }
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(file_str_test_suite)

    BOOST_AUTO_TEST_CASE(test_extract_file_path) {
        BOOST_TEST(extractFilePath("C:\\lsrm\\test\\text.txt") == "C:\\lsrm\\test\\");
    }

    BOOST_AUTO_TEST_CASE(test_extract_file_name) {
        BOOST_TEST(extractFileName("C:\\lsrm\\test\\text.txt") == "text.txt");
    }

    BOOST_AUTO_TEST_CASE(test_extract_file_ext) {
        BOOST_TEST(extractFileExt("C:\\lsrm\\test\\test.txt") == string(".txt"));
        BOOST_TEST(extractFileExt("C:\\lsrm\\test\\test") == string(""));
    }

    BOOST_AUTO_TEST_CASE(test_level_up) {
        BOOST_TEST(goOneLevelUp("C:\\lsrm\\test\\") == "C:\\lsrm\\");
        BOOST_TEST(goOneLevelUp("C:\\lsrm\\test") == "C:\\lsrm\\");
        BOOST_TEST(goOneLevelUp("C:\\lsrm\\") == "C:\\");
        BOOST_TEST(goOneLevelUp("C:\\") == "C:\\");
    }

    BOOST_AUTO_TEST_CASE(test_expand_file_path) {
        // simple variants
        BOOST_TEST(expandFileNamesToRelBaseDir("C:\\lsrm\\test\\test.txt", "C:\\") == "C:\\lsrm\\test\\test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("test.txt", "C:\\lsrm\\") == "C:\\lsrm\\test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("test.txt", "C:\\lsrm") == string("C:\\lsrm") + getSlash() + "test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("test\\test.txt", "C:\\lsrm\\") == "C:\\lsrm\\test\\test.txt");
        // variants with ".."
        BOOST_TEST(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\test\\") == "C:\\lsrm\\test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\test") == "C:\\lsrm\\test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\") == "C:\\test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm") == "C:\\test.txt");
        BOOST_TEST(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\") == "C:\\test.txt");
    }

BOOST_AUTO_TEST_SUITE_END()
