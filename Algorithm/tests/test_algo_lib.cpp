#define BOOST_TEST_MODULE math_test_module
#include <boost/test/unit_test.hpp>
#include <utility>
#include <vector>
#include <iostream>

#include "../double_counter_map.h"
#include "../algo_lib.h"
#include "../dictionary.h"

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


BOOST_AUTO_TEST_SUITE(double_counter_map_test_suite)

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


BOOST_AUTO_TEST_SUITE(algo_lib_test_suite)

    BOOST_AUTO_TEST_CASE(test_sumEqual) {
        {
            vector<pair<int, int>> v{
                {1, 1},
                {2, 1}, {2, 1},
                {3, 1},
                {4, 1}, {4, 1}, {4, 1},
                {5, 1}, {5, 1}};
            vector<pair<int, int>> expected{{1, 1}, {2, 2}, {3, 1}, {4, 3}, {5, 2}};
            v.erase(
                sumEqual(v.begin(), v.end(),
                        [](const auto& lhs, const auto& rhs){ return lhs.first == rhs.first;},
                        [](auto& target, const auto& item){target.second += item.second;}
                        ),
                v.end()
            );

            BOOST_TEST(v == expected);
        }
        {
            vector<pair<int, int>> v{};
            vector<pair<int, int>> expected{};
            v.erase(
                sumEqual(v.begin(), v.end(),
                        [](const auto& lhs, const auto& rhs){ return lhs.first == rhs.first;},
                        [](auto& target, const auto& item){target.second += item.second;}
                        ),
                v.end()
            );

            BOOST_TEST(v == expected);
        }
        {
            vector<pair<int, int>> v{{1, 1}};
            vector<pair<int, int>> expected{{1, 1}};
            v.erase(
                sumEqual(v.begin(), v.end(),
                        [](const auto& lhs, const auto& rhs){ return lhs.first == rhs.first;},
                        [](auto& target, const auto& item){target.second += item.second;}
                        ),
                v.end()
            );

            BOOST_TEST(v == expected);
        }
        {
            vector<pair<int, int>> v{{1, 1}, {2, 1}, {1, 1}};
            vector<pair<int, int>> expected{{1, 1}, {2, 1}, {1, 1}};
            v.erase(
                sumEqual(v.begin(), v.end(),
                        [](const auto& lhs, const auto& rhs){ return lhs.first == rhs.first;},
                        [](auto& target, const auto& item){target.second += item.second;}
                        ),
                v.end()
            );

            BOOST_TEST(v == expected);
        }
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dictionary_test_suite)

    BOOST_AUTO_TEST_CASE(test_simple_dict) {
        {
            Dict<int, int> d;
            BOOST_TEST(d.empty());
            BOOST_TEST(d.size() == 0u);
        }
        {
            Dict<int, int> d;
            BOOST_TEST(d.count(0) == 0u);
            BOOST_TEST(!d.contains(0));
            d[0] = 1;
            BOOST_TEST(!d.empty());
            BOOST_TEST(d.size() == 1u);
            BOOST_TEST(d.count(0) == 1u);
            BOOST_TEST(d.contains(0));
            BOOST_TEST(d.at(0) == 1);
            BOOST_TEST(d[0] == 1);
            d[0] = 2;
            BOOST_TEST(d.size() == 1u);
            BOOST_TEST(d.count(0) == 1u);
            BOOST_TEST(d.contains(0));
            BOOST_TEST(d.count(1) == 0u);
            BOOST_TEST(!d.contains(1));
            BOOST_TEST(d.at(0) == 2);
            BOOST_TEST(d[0] == 2);
            d[1] = 3;
            BOOST_TEST(d.size() == 2u);
            BOOST_TEST(d.count(0) == 1u);
            BOOST_TEST(d.contains(0));
            BOOST_TEST(d.count(1) == 1u);
            BOOST_TEST(d.contains(1));
            BOOST_TEST(d.at(0) == 2);
            BOOST_TEST(d[0] == 2);
            BOOST_TEST(d.at(1) == 3);
            BOOST_TEST(d[1] == 3);
            std::size_t erased_count = d.erase(10);
            BOOST_TEST(erased_count == 0u);
            erased_count = d.erase(0);
            BOOST_TEST(erased_count == 1u);
            BOOST_TEST(d.size() == 1u);
            BOOST_TEST(d.count(0) == 0u);
            BOOST_TEST(!d.contains(0));
            BOOST_TEST(d.count(1) == 1u);
            BOOST_TEST(d.contains(1));
            BOOST_TEST(d.at(1) == 3);
            erased_count = d.erase(1);
            BOOST_TEST(erased_count == 1u);
            BOOST_TEST(d.empty());
        }
    }

    BOOST_AUTO_TEST_CASE(test_iterate_dict_order) {
        Dict<std::string, int> d;
        d["one"] = 1;
        d["two"] = 2;
        d["three"] = 3;
        d["zero"] = 0;
        std::vector<std::pair<std::string, int>> expected{
            std::pair{"one", 1},
            std::pair{"two", 2},
            std::pair{"three", 3},
            std::pair{"zero", 0},
        };

        std::size_t i = 0;
        for (const auto& [k, v] : d) {
            const auto& [ke, ve] = expected[i];
            BOOST_TEST(k == ke);
            BOOST_TEST(v == ve);
            i++;
        }
    }

BOOST_AUTO_TEST_SUITE_END()
