#include <doctest/doctest.h>

#include <string>
#include <vector>

#include "fileutils.h"

using namespace std;
using namespace gwstr;

std::string SEP = std::string(1, OS_SEP);

TEST_SUITE("file_str_test_suite") {

    TEST_CASE("test_extract_file_path") {
        CHECK(extractFilePath("C:" + SEP + "foo" + SEP + "test" + SEP + "text.txt") == "C:" + SEP + "foo" + SEP + "test" + SEP + "");
    }

    TEST_CASE("test_extract_file_name") {
        CHECK(extractFileName("C:" + SEP + "foo" + SEP + "test" + SEP + "text.txt") == "text.txt");
    }

    TEST_CASE("test_extract_file_ext") {
        CHECK(extractFileExt("C:" + SEP + "foo" + SEP + "test" + SEP + "test.txt") == string(".txt"));
        CHECK(extractFileExt("C:" + SEP + "foo" + SEP + "test" + SEP + "test") == string(""));
        CHECK(extractFileExt("C:" + SEP + "foo" + SEP + "test.bar" + SEP + "test") == string(""));
    }

    TEST_CASE("test_path_split") {
        CHECK(pathSplit("C:" + SEP + "foo" + SEP + "test" + SEP + "text.txt") == make_tuple("C:" + SEP + "foo" + SEP + "test" + SEP + "", "text.txt"));
    }

    TEST_CASE("test_path_split_ext") {
        CHECK(pathSplitExt("C:" + SEP + "foo" + SEP + "test" + SEP + "text.txt") == make_tuple("C:" + SEP + "foo" + SEP + "test" + SEP + "text", ".txt"));
    }

    TEST_CASE("test_path_join") {
        CHECK(pathJoin("C:" + SEP + "foo" + SEP, "text.txt") == "C:" + SEP + "foo" + SEP + "text.txt");
        CHECK(pathJoin("C:" + SEP + "foo", "text.txt") == "C:" + SEP + "foo" + SEP + "text.txt");
    }

    TEST_CASE("test_parent_directory") {
        CHECK(parentDirectory("C:" + SEP + "foo" + SEP + "test" + SEP + "") == "C:" + SEP + "foo" + SEP + "");
        CHECK(parentDirectory("C:" + SEP + "foo" + SEP + "test") == "C:" + SEP + "foo" + SEP + "");
        CHECK(parentDirectory("C:" + SEP + "foo" + SEP + "") == "C:" + SEP + "");
        CHECK(parentDirectory("C:" + SEP + "") == "C:" + SEP + "");
    }

    TEST_CASE("test_expand_file_path") {
        // simple variants
        CHECK(expandFileNamesToRelBaseDir("C:" + SEP + "foo" + SEP + "test" + SEP + "test.txt", "C:" + SEP + "") == "C:" + SEP + "foo" + SEP + "test" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir("test.txt", "C:" + SEP + "foo" + SEP + "") == "C:" + SEP + "foo" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir("test.txt", "C:" + SEP + "foo") == "C:" + SEP + "foo" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir("test" + SEP + "test.txt", "C:" + SEP + "foo" + SEP + "") == "C:" + SEP + "foo" + SEP + "test" + SEP + "test.txt");
        // variants with ".."
        CHECK(expandFileNamesToRelBaseDir(".." + SEP + "test.txt", "C:" + SEP + "foo" + SEP + "test" + SEP + "") == "C:" + SEP + "foo" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir(".." + SEP + "test.txt", "C:" + SEP + "foo" + SEP + "test") == "C:" + SEP + "foo" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir(".." + SEP + "test.txt", "C:" + SEP + "foo" + SEP + "") == "C:" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir(".." + SEP + "test.txt", "C:" + SEP + "foo") == "C:" + SEP + "test.txt");
        CHECK(expandFileNamesToRelBaseDir(".." + SEP + "test.txt", "C:" + SEP + "") == "C:" + SEP + "test.txt");
    }

}
