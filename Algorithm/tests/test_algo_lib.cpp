#define BOOST_TEST_MODULE math_test_module
#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>

#include "../double_counter_map.h"

using namespace std;
namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

/*
template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec) {
    for (const auto& v : vec) {
        out << v << " ";
    }
    return out;
}
*/
/*
template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, std::map<K,V> dict) {
    for (const auto& [k,v] : dict) {
        out << k << ": " << v << ", ";
    }
    return out;
}
*/


BOOST_AUTO_TEST_SUITE(algo_lib_test_suite)

    BOOST_AUTO_TEST_CASE(test_double_map) {
        // add 2 different values
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.2);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 2u);
            BOOST_TEST(d.at(1.1) == 1);
            BOOST_TEST(d.at(1.2) == 1);
        }
        // add bigger close values in the end
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.109);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 1u);
            BOOST_TEST(d.at(1.1) == 2);
        }
        // add smaller close values in the end
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.091);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 1u);
            BOOST_TEST(d.at(1.1) == 2);
        }
        // add bigger close values in the middle
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(1.109);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 3u);
            BOOST_TEST(d.at(1.1) == 2);
            BOOST_TEST(d.at(1.0) == 1);
            BOOST_TEST(d.at(1.2) == 1);
        }
        // add smaller close values in the middle
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(1.091);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 3u);
            BOOST_TEST(d.at(1.1) == 2);
            BOOST_TEST(d.at(1.0) == 1);
            BOOST_TEST(d.at(1.2) == 1);
        }
        // add bigger close values in the begin
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(1.009);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 3u);
            BOOST_TEST(d.at(1.1) == 1);
            BOOST_TEST(d.at(1.0) == 2);
            BOOST_TEST(d.at(1.2) == 1);
        }
        // add smaller close values in the begin
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(0.991);
            const auto& d = dict.getCounterDict();
            BOOST_TEST(d.size() == 3u);
            BOOST_TEST(d.at(1.1) == 1);
            BOOST_TEST(d.at(1.0) == 2);
            BOOST_TEST(d.at(1.2) == 1);
        }
    }

BOOST_AUTO_TEST_SUITE_END()