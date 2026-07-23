#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <string>
#include <vector>
#include <sstream>

#include "iniparser.h"

using namespace std;

TEST_SUITE("str_test_suite") {

    TEST_CASE("test_read_ini_str_anon_section") {
        stringstream ss;
        ss  << "key1=value1\n"
            << "key2=value2\n"
            << "key5 = value5\n";
        IniParser ini(ss);
        CHECK(ini.getStringValue("", "key1") == "value1");
        CHECK(ini.getStringValue("", "key2") == "value2");
        CHECK(ini.getStringValue("section_name", "key1") == "");
        CHECK(ini.getStringValue("", "key4") == "");
        CHECK(ini.getStringValue("", "key5") == "value5");
    }

    TEST_CASE("test_read_ini_simple_types") {
        std::string section_name = "section";
        stringstream ss;
        ss  << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        IniParser ini(ss);
        CHECK(ini.getStringValue(section_name, "key1") == "4");
        CHECK(ini.getStringValue("", "key1") == "");
        CHECK(ini.getStringValue(section_name, "key2") == "2.5");
        CHECK(ini.getStringValue(section_name, "key3") == "true");
        CHECK(ini.getStringValue(section_name, "key4") == "4");
        CHECK(ini.getValue<int>(section_name, "key1") == 4);
        CHECK(ini.getValue<double>(section_name, "key2") == 2.5);
        CHECK(ini.getValue<bool>(section_name, "key3"));
        CHECK(ini.getValue<int>(section_name, "key2") == 2);
        CHECK_THROWS_AS(ini.getValue<double>("s", "key2"), std::exception);
    }

    TEST_CASE("test_read_ini_with_def_value") {
        std::string section_name = "section";
        stringstream ss;
        ss  << "[" << section_name << "]\n"
            << "key1=4\n"
            << "key2=2.5\n"
            << "key3=true\n"
            << "key4 = 4\n";
        IniParser ini(ss);
        CHECK(ini.getValueDef<int>(section_name, "key1", 5) == 4);
        CHECK(ini.getValueDef<double>(section_name, "key2", 4) == 2.5);
        CHECK(ini.getValueDef<bool>(section_name, "key3", false));
        CHECK(ini.getValueDef<int>(section_name, "key4", 2) == 4);
        CHECK(ini.getValueDef<int>(section_name, "key5", 6) == 6);
        CHECK(ini.getValueDef<bool>(section_name, "key6", false) == false);
        CHECK(ini.getValueDef<int>("s", "key1", 2) == 2);
    }

    TEST_CASE("test_write_ini") {
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
        CHECK(out.str() == expected_str);
    }

    TEST_CASE("test_write_complicated_ini") {
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
        CHECK(out.str() == expected_str);
    }

    TEST_CASE("test_add_values") {
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
        CHECK(out.str() == expected_str);
    }

}
