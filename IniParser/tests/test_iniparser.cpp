#define BOOST_TEST_MODULE str_test_module
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <sstream>

#include "iniparser.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(str_test_suite)

    BOOST_AUTO_TEST_CASE(test_read_ini_str_anon_section) {
        stringstream ss;
        ss  << "key1=value1\n"
            << "key2=value2\n"
            << "key5 = value5\n";
        IniParser ini(ss);
        BOOST_TEST(
                ini.getStringValue("", "key1") == "value1"
        );
        BOOST_TEST(
                ini.getStringValue("", "key2") == "value2"
        );
        BOOST_TEST(
                ini.getStringValue("section_name", "key1") == ""
        );
        BOOST_TEST(
                ini.getStringValue("", "key4") == ""
        );
        BOOST_TEST(
                ini.getStringValue("", "key5") == "value5"
        );
    }

    BOOST_AUTO_TEST_CASE(test_read_ini_simple_types) {
        std::string section_name = "section";
        stringstream ss;
        ss  << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        IniParser ini(ss);
        BOOST_TEST(
                ini.getStringValue(section_name, "key1") == "4"
        );
        BOOST_TEST(
                ini.getStringValue("", "key1") == ""
        );
        BOOST_TEST(
                ini.getStringValue(section_name, "key2") == "2.5"
        );
        BOOST_TEST(
                ini.getStringValue(section_name, "key3") == "true"
        );
        BOOST_TEST(
                ini.getStringValue(section_name, "key4") == "4"
        );
        BOOST_TEST(
                ini.getValue<int>(section_name, "key1") == 4
        );
        BOOST_TEST(
                ini.getValue<double>(section_name, "key2") == 2.5
        );
        BOOST_TEST(
                ini.getValue<bool>(section_name, "key3")
        );
        BOOST_TEST(
                ini.getValue<int>(section_name, "key2") == 2
        );
        BOOST_CHECK_THROW(
                ini.getValue<double>("s", "key2") == 2.5,
                std::exception
        );
    }

    BOOST_AUTO_TEST_CASE(test_read_ini_with_def_value) {
        std::string section_name = "section";
        stringstream ss;
        ss  << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        IniParser ini(ss);
        BOOST_TEST(
                ini.getValueDef<int>(section_name, "key1", 5) == 4
        );
        BOOST_TEST(
                ini.getValueDef<double>(section_name, "key2", 4) == 2.5
        );
        BOOST_TEST(
                ini.getValueDef<bool>(section_name, "key3", false)
        );
        BOOST_TEST(
                ini.getValueDef<int>(section_name, "key4", 2) == 4
        );
        BOOST_TEST(
                ini.getValueDef<int>(section_name, "key5", 6) == 6
        );
        BOOST_TEST(
                ini.getValueDef<bool>(section_name, "key6", false) == false
        );
        BOOST_TEST(
                ini.getValueDef<int>("s", "key1", 2) == 2
        );
    }

    BOOST_AUTO_TEST_CASE(test_write_ini) {
        std::string section_name = "section";
        stringstream ss;
        ss  << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        IniParser ini(ss);

        stringstream out;
        ini.writeToStream(out);
        std::string expected_str =
            "[" + section_name + "]\n"
            "key1=4\n"
            "key2=2.5\n"
            "key3=true\n"
            "key4=4\n";
        BOOST_TEST(
                out.str() == expected_str
        );
    }

    BOOST_AUTO_TEST_CASE(test_write_complicated_ini) {
        std::string section_name = "section";
        stringstream ss;
        ss  << "k1=1\n"
            << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        IniParser ini(ss);

        stringstream out;
        ini.writeToStream(out);
        std::string expected_str =
            "k1=1\n"
            "[" + section_name + "]\n"
            "key1=4\n"
            "key2=2.5\n"
            "key3=true\n"
            "key4=4\n";
        BOOST_TEST(
                out.str() == expected_str
        );
    }

    BOOST_AUTO_TEST_CASE(test_add_values) {
        std::string section_name = "section";
        stringstream ss;
        ss  << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = some string\n";
        IniParser ini(ss);

        ini.setValue(section_name, "key5", "some_str");
        ini.setValue(section_name, "key1", 1);
        ini.setValue(section_name, "key2", 1.5);
        ini.setValue(section_name, "key3", false);
        ini.setValue(section_name, "key4", "another string");

        stringstream out;
        ini.writeToStream(out);
        std::string expected_str =
            "[" + section_name + "]\n"
            "key1=1\n"
            "key2=1.500000\n"
            "key3=false\n"
            "key4=another string\n"
            "key5=some_str\n";
        BOOST_TEST(
                out.str() == expected_str
        );
    }

BOOST_AUTO_TEST_SUITE_END()
