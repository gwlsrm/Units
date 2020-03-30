#define BOOST_TEST_MODULE str_test_module
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <sstream>

#include "cnfreader.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(str_test_suite)

    BOOST_AUTO_TEST_CASE(test_read_cnf_str) {
        stringstream ss;
        ss  << "key1=value1\n"
            << "key2=value2\n"
            << "key3=value3\n"
            << "key5 = value5\n";
        CnfReader cnf(ss, "=");
        BOOST_TEST(
                cnf.getStringValue("key1") == "value1"
        );
        BOOST_TEST(
                cnf.getStringValue("key2") == "value2"
        );
        BOOST_TEST(
                cnf.getStringValue("key3") == "value3"
        );
        BOOST_TEST(
                cnf.getStringValue("key4") == ""
        );
        BOOST_TEST(
                cnf.getStringValue("key5") == "value5"
        );
    }

    BOOST_AUTO_TEST_CASE(test_read_cnf_simple_types) {
        stringstream ss;
        ss  << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        CnfReader cnf(ss, "=");
        BOOST_TEST(
                cnf.getStringValue("key1") == "4"
        );
        BOOST_TEST(
                cnf.getStringValue("key2") == "2.5"
        );
        BOOST_TEST(
                cnf.getStringValue("key3") == "true"
        );
        BOOST_TEST(
                cnf.getStringValue("key4") == "4"
        );
        BOOST_TEST(
                cnf.getValue<int>("key1") == 4
        );
        BOOST_TEST(
                cnf.getValue<double>("key2") == 2.5
        );
        BOOST_TEST(
                cnf.getValue<bool>("key3")
        );
        BOOST_TEST(
                cnf.getValue<int>("key2") == 2
        );
    }

    BOOST_AUTO_TEST_CASE(test_read_cnf_values_with_units) {
        stringstream ss;
        ss  << "key1=4.5 cm\n"
            << "key2=2.5\n"
            << "key3 = 1 kg\n";
        CnfReader cnf(ss, "=");
        BOOST_TEST(
                cnf.getValue<double>("key1") == 4.5
        );
        BOOST_TEST(
                cnf.getValue<double>("key2") == 2.5
        );
        BOOST_TEST(
                cnf.getValue<double>("key3") == 1
        );
    }

BOOST_AUTO_TEST_SUITE_END()