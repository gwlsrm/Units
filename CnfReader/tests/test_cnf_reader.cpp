#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <string>
#include <vector>
#include <sstream>

#include "cnfreader.h"

using namespace std;

TEST_SUITE("str_test_suite") {

    TEST_CASE("test_read_cnf_str") {
        stringstream ss;
        ss  << "key1=value1\n"
            << "key2=value2\n"
            << "key3=value3\n"
            << "key5 = value5\n";
        CnfReader cnf(ss, "=");
        CHECK(cnf.getStringValue("key1") == "value1");
        CHECK(cnf.getStringValue("key2") == "value2");
        CHECK(cnf.getStringValue("key3") == "value3");
        CHECK(cnf.getStringValue("key4") == "");
        CHECK(cnf.getStringValue("key5") == "value5");
    }

    TEST_CASE("test_read_cnf_simple_types") {
        stringstream ss;
        ss  << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        CnfReader cnf(ss, "=");
        CHECK(cnf.getStringValue("key1") == "4");
        CHECK(cnf.getStringValue("key2") == "2.5");
        CHECK(cnf.getStringValue("key3") == "true");
        CHECK(cnf.getStringValue("key4") == "4");
        CHECK(cnf.getValue<int>("key1") == 4);
        CHECK(cnf.getValue<double>("key2") == 2.5);
        CHECK(cnf.getValue<bool>("key3"));
        CHECK(cnf.getValue<int>("key2") == 2);
    }

    TEST_CASE("test_read_cnf_values_with_units") {
        stringstream ss;
        ss  << "key1=4.5 cm\n"
            << "key2=2.5\n"
            << "key3 = 1 kg\n";
        CnfReader cnf(ss, "=");
        CHECK(cnf.getValue<double>("key1") == 4.5);
        CHECK(cnf.getValue<double>("key2") == 2.5);
        CHECK(cnf.getValue<double>("key3") == 1);
    }

    TEST_CASE("test_read_cnf_with_def_value") {
        stringstream ss;
        ss  << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        CnfReader cnf(ss, "=");
        CHECK(cnf.getValueDef<int>("key1", 5) == 4);
        CHECK(cnf.getValueDef<double>("key2", 4) == 2.5);
        CHECK(cnf.getValueDef<bool>("key3", false));
        CHECK(cnf.getValueDef<int>("key4", 2) == 4);
        CHECK(cnf.getValueDef<int>("key5", 6) == 6);
        CHECK(cnf.getValueDef<bool>("key6", false) == false);
    }

}
