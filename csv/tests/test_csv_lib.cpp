#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <sstream>
#include <vector>
#include <string>

#include "csv_writer.h"

using namespace std;


TEST_SUITE("csv_lib_writer_test_suite") {

    TEST_CASE("test_write_int") {
        stringstream ss;
        CsvWriter csv(ss);
        csv << 1;
        CHECK(ss.str() == "1");
        csv << 2;
        CHECK(ss.str() == "1,2");
        csv << 3;
        csv.endLine();
        CHECK(ss.str() == "1,2,3\n");
    }

    TEST_CASE("test_write_double") {
        stringstream ss;
        CsvWriter csv(ss);
        csv << 1.1;
        CHECK(ss.str() == "1.1");
        csv << 2.3;
        CHECK(ss.str() == "1.1,2.3");
        csv << 3.0;
        csv.endLine();
        CHECK(ss.str() == "1.1,2.3,3\n");
    }

    TEST_CASE("test_write_char") {
        stringstream ss;
        CsvWriter csv(ss);
        csv << 'a';
        CHECK(ss.str() == "a");
        csv << 'b';
        CHECK(ss.str() == "a,b");
        csv << 'c';
        csv.endLine();
        CHECK(ss.str() == "a,b,c\n");
    }

    TEST_CASE("test_write_string") {
        stringstream ss;
        CsvWriter csv(ss);
        csv << "abc"s;
        CHECK(ss.str() == "\"abc\"");
        csv << "bca"s;
        CHECK(ss.str() == "\"abc\",\"bca\"");
        csv << "x"s;
        csv.endLine();
        CHECK(ss.str() == "\"abc\",\"bca\",\"x\"\n");
    }

    TEST_CASE("test_write_string_view") {
        stringstream ss;
        CsvWriter csv(ss);
        csv << "abc"sv;
        CHECK(ss.str() == "\"abc\"");
        csv << "bca"sv;
        CHECK(ss.str() == "\"abc\",\"bca\"");
        csv << "x"sv;
        csv.endLine();
        CHECK(ss.str() == "\"abc\",\"bca\",\"x\"\n");
    }

    TEST_CASE("test_write_vector_view") {
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v{1, 2, 3, 4, 5};
            csv.writeLine(v);
            CHECK(ss.str() == "1,2,3,4,5");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v{1, 2, 3, 4, 5};
            csv.writeLine(v, true);
            CHECK(ss.str() == "1,2,3,4,5\n");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v1{1, 2, 3, 4, 5};
            vector<int> v2{4, 3, 2, 1, 0};
            csv.writeLine(v1, true);
            csv.writeLine(v2, true);
            CHECK(ss.str() == "1,2,3,4,5\n4,3,2,1,0\n");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v1{1, 2, 3, 4, 5};
            vector<int> v2{4, 3, 2, 1, 0};
            csv.writeLine(v1, false);
            csv.writeLine(v2, true);
            CHECK(ss.str() == "1,2,3,4,5,4,3,2,1,0\n");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<string> v{"1", "2", "3", "4", "5"};
            csv.writeLine(v);
            CHECK(ss.str() == "\"1\",\"2\",\"3\",\"4\",\"5\"");
        }
    }

}
