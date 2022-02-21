#define BOOST_TEST_MODULE math_test_module
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <vector>
#include <string>

#include "csv_writer.h"

using namespace std;


BOOST_AUTO_TEST_SUITE(csv_lib_writer_test_suite)

    BOOST_AUTO_TEST_CASE(test_write_int) {
        stringstream ss;
        CsvWriter csv(ss);
        csv << 1;
        BOOST_TEST(ss.str() == "1");
        csv << 2;
        BOOST_TEST(ss.str() == "1,2");
        csv << 3;
        csv.endLine();
        BOOST_TEST(ss.str() == "1,2,3\n");
    }

    BOOST_AUTO_TEST_CASE(test_write_double) {
        stringstream ss;
        CsvWriter csv(ss);
        csv << 1.1;
        BOOST_TEST(ss.str() == "1.1");
        csv << 2.3;
        BOOST_TEST(ss.str() == "1.1,2.3");
        csv << 3.0;
        csv.endLine();
        BOOST_TEST(ss.str() == "1.1,2.3,3\n");
    }

    BOOST_AUTO_TEST_CASE(test_write_char) {
        stringstream ss;
        CsvWriter csv(ss);
        csv << 'a';
        BOOST_TEST(ss.str() == "a");
        csv << 'b';
        BOOST_TEST(ss.str() == "a,b");
        csv << 'c';
        csv.endLine();
        BOOST_TEST(ss.str() == "a,b,c\n");
    }

    BOOST_AUTO_TEST_CASE(test_write_string) {
        stringstream ss;
        CsvWriter csv(ss);
        csv << "abc"s;
        BOOST_TEST(ss.str() == "\"abc\"");
        csv << "bca"s;
        BOOST_TEST(ss.str() == "\"abc\",\"bca\"");
        csv << "x"s;
        csv.endLine();
        BOOST_TEST(ss.str() == "\"abc\",\"bca\",\"x\"\n");
    }

    BOOST_AUTO_TEST_CASE(test_write_string_view) {
        stringstream ss;
        CsvWriter csv(ss);
        csv << "abc"sv;
        BOOST_TEST(ss.str() == "\"abc\"");
        csv << "bca"sv;
        BOOST_TEST(ss.str() == "\"abc\",\"bca\"");
        csv << "x"sv;
        csv.endLine();
        BOOST_TEST(ss.str() == "\"abc\",\"bca\",\"x\"\n");
    }

    BOOST_AUTO_TEST_CASE(test_write_vector_view) {
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v{1, 2, 3, 4, 5};
            csv.writeLine(v);
            BOOST_TEST(ss.str() == "1,2,3,4,5");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v{1, 2, 3, 4, 5};
            csv.writeLine(v, true);
            BOOST_TEST(ss.str() == "1,2,3,4,5\n");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v1{1, 2, 3, 4, 5};
            vector<int> v2{4, 3, 2, 1, 0};
            csv.writeLine(v1, true);
            csv.writeLine(v2, true);
            BOOST_TEST(ss.str() == "1,2,3,4,5\n4,3,2,1,0\n");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<int> v1{1, 2, 3, 4, 5};
            vector<int> v2{4, 3, 2, 1, 0};
            csv.writeLine(v1, false);
            csv.writeLine(v2, true);
            BOOST_TEST(ss.str() == "1,2,3,4,5,4,3,2,1,0\n");
        }
        {
            stringstream ss;
            CsvWriter csv(ss);
            vector<string> v{"1", "2", "3", "4", "5"};
            csv.writeLine(v);
            BOOST_TEST(ss.str() == "\"1\",\"2\",\"3\",\"4\",\"5\"");
        }
    }

BOOST_AUTO_TEST_SUITE_END()