#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <string>
#include <vector>

#include "str_utils.h"
#include "fileutils.h"

using namespace std;
using namespace gwstr;

TEST_SUITE("str_test_suite") {

    TEST_CASE("test_str_trim") {
        string expected = "test string";
        CHECK(trim("   test string   ") == expected);
        CHECK(trim("   test string") == expected);
        CHECK(trim("test string   ") == expected);
        CHECK(trim("test string") == expected);
        CHECK(trim(" ") == ""s);
        CHECK(trim("\n") == ""s);
    }

    TEST_CASE("test_str_trim_right") {
        CHECK(trim_right("   test string   ") == "   test string"sv);
        CHECK(trim_right("   test string") == "   test string"sv);
        CHECK(trim_right("test string   ") == "test string"sv);
        CHECK(trim_right("test string") == "test string"sv);
        CHECK(trim_right(" ") == ""s);
        CHECK(trim_right("\n") == ""s);
    }

    TEST_CASE("test_str_trim_left") {
        CHECK(trim_left("   test string   ") == "test string   "sv);
        CHECK(trim_left("   test string") == "test string"sv);
        CHECK(trim_left("test string   ") == "test string   "sv);
        CHECK(trim_left("test string") == "test string"sv);
        CHECK(trim_left(" ") == ""s);
        CHECK(trim_left("\n") == ""s);
    }

    TEST_CASE("test_tolower") {
        CHECK(str_tolower("Test string") == "test string"sv);
        CHECK(str_tolower("TesT StrIng") == "test string"sv);
        CHECK(str_tolower("test string") == "test string"sv);
    }

    TEST_CASE("test_toupper") {
        CHECK(str_toupper("Test string") == "TEST STRING"sv);
        CHECK(str_toupper("TesT StrIng") == "TEST STRING"sv);
        CHECK(str_toupper("test string") == "TEST STRING"sv);
    }

    TEST_CASE("test_starts_with") {
        CHECK(starts_with("Test string", "Test"));
        CHECK(starts_with("Test string"s, "Test"s));
        CHECK(starts_with("  Test string"s, "  Test"s));
        CHECK(starts_with("  Test"s, "  Test"s));
        CHECK(starts_with("  Test string"s, "  Test "s));
        CHECK(starts_with("  Test string", "  Test "));
        CHECK(!starts_with("Test", "Test string"));
        CHECK(starts_with(" "s, ""s));
    }

    TEST_CASE("test_endswith") {
        CHECK(ends_with("Test string"s, "string"s));
        CHECK(ends_with("Test string  "s, "tring  "s));
        CHECK(!ends_with("Test string  "s, "tring"s));
        CHECK(!ends_with("string"sv, "Test string"));
    }

    TEST_CASE("test_same_text") {
        CHECK(same_text("Test string"s, "test String"s));
        CHECK(!same_text("Test string"s, "tes String"s));
    }

    TEST_CASE("test_join_strings") {
        CHECK(join_strings({"str1", "str2", "str3"}) == "str1 str2 str3"sv);
        CHECK(join_strings({"str1", "str2", "str3"}, ',') == "str1,str2,str3"sv);
        const vector<string> si {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        CHECK(
            join_strings({"-" + si[5], "-" + si[10], si[2], "(", si[9], ":", si[4], ")"}) ==
            "-" + si[5] + " -" + si[10] + " " + si[2] + " ( " + si[9] + " : " + si[4] + " )"
        );
    }

    TEST_CASE("test_split_into_words") {
        {
            string str = "a1 a2 a3";
            auto res = split_into_words(str);
            vector<string> expected = {"a1", "a2", "a3"};
            CHECK(res == expected);
        }
        {
            string str = " a1 a2 a3";
            auto res = split_into_words(str);
            vector<string> expected = {"a1", "a2", "a3"};
            CHECK(res == expected);
        }
        {
            string str = "a1 a2 a3 ";
            auto res = split_into_words(str);
            vector<string> expected = {"a1", "a2", "a3"};
            CHECK(res == expected);
        }
    }

}

TEST_SUITE("file_str_test_suite") {

    TEST_CASE("test_extract_file_path") {
        CHECK(extractFilePath("C:\\lsrm\\test\\text.txt") == "C:\\lsrm\\test\\");
    }

    TEST_CASE("test_extract_file_name") {
        CHECK(extractFileName("C:\\lsrm\\test\\text.txt") == "text.txt");
    }

    TEST_CASE("test_extract_file_ext") {
        CHECK(extractFileExt("C:\\lsrm\\test\\test.txt") == string(".txt"));
        CHECK(extractFileExt("C:\\lsrm\\test\\test") == string(""));
    }

    TEST_CASE("test_level_up") {
        CHECK(goOneLevelUp("C:\\lsrm\\test\\") == "C:\\lsrm\\");
        CHECK(goOneLevelUp("C:\\lsrm\\test") == "C:\\lsrm\\");
        CHECK(goOneLevelUp("C:\\lsrm\\") == "C:\\");
        CHECK(goOneLevelUp("C:\\") == "C:\\");
    }

    TEST_CASE("test_expand_file_path") {
        // simple variants
        CHECK(expandFileNamesToRelBaseDir("C:\\lsrm\\test\\test.txt", "C:\\") == "C:\\lsrm\\test\\test.txt");
        CHECK(expandFileNamesToRelBaseDir("test.txt", "C:\\lsrm\\") == "C:\\lsrm\\test.txt");
        CHECK(expandFileNamesToRelBaseDir("test.txt", "C:\\lsrm") == string("C:\\lsrm") + getSlash() + "test.txt");
        CHECK(expandFileNamesToRelBaseDir("test\\test.txt", "C:\\lsrm\\") == "C:\\lsrm\\test\\test.txt");
        // variants with ".."
        CHECK(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\test\\") == "C:\\lsrm\\test.txt");
        CHECK(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\test") == "C:\\lsrm\\test.txt");
        CHECK(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\") == "C:\\test.txt");
        CHECK(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm") == "C:\\test.txt");
        CHECK(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\") == "C:\\test.txt");
    }

}
