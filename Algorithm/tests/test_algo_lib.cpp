#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <utility>
#include <vector>
#include <iostream>

#include "../double_counter_map.h"
#include "../algo_lib.h"
#include "../dictionary.h"

using namespace std;


TEST_SUITE("double_counter_map_test_suite") {

    TEST_CASE("test_double_map") {
        // add 2 different values
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.2);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 2u);
            CHECK(d.at(1.1) == 1);
            CHECK(d.at(1.2) == 1);
        }
        // add bigger close values in the end
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.109);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 1u);
            CHECK(d.at(1.1) == 2);
        }
        // add smaller close values in the end
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.091);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 1u);
            CHECK(d.at(1.1) == 2);
        }
        // add bigger close values in the middle
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(1.109);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 3u);
            CHECK(d.at(1.1) == 2);
            CHECK(d.at(1.0) == 1);
            CHECK(d.at(1.2) == 1);
        }
        // add smaller close values in the middle
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(1.091);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 3u);
            CHECK(d.at(1.1) == 2);
            CHECK(d.at(1.0) == 1);
            CHECK(d.at(1.2) == 1);
        }
        // add bigger close values in the begin
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(1.009);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 3u);
            CHECK(d.at(1.1) == 1);
            CHECK(d.at(1.0) == 2);
            CHECK(d.at(1.2) == 1);
        }
        // add smaller close values in the begin
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.0);
            dict.add_value(1.2);
            dict.add_value(0.991);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 3u);
            CHECK(d.at(1.1) == 1);
            CHECK(d.at(1.0) == 2);
            CHECK(d.at(1.2) == 1);
        }
        // inc value_cnt
        {
            DoubleCounterMap<int> dict{0.01};
            dict.add_value(1.1);
            dict.add_value(1.109);
            dict.add_value(1.0);
            dict.inc_value_cnt(1.101, 3);
            dict.inc_value_cnt(2.0, 4);
            const auto& d = dict.getCounterDict();
            CHECK(d.size() == 3u);
            CHECK(d.at(1.1) == 5);
            CHECK(d.at(1.0) == 1);
            CHECK(d.at(2.0) == 4);
        }
    }

}


TEST_SUITE("algo_lib_test_suite") {

    TEST_CASE("test_sumEqual") {
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

            CHECK(v == expected);
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

            CHECK(v == expected);
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

            CHECK(v == expected);
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

            CHECK(v == expected);
        }
    }

}


TEST_SUITE("dictionary_test_suite") {

    TEST_CASE("test_simple_dict") {
        {
            Dict<int, int> d;
            CHECK(d.empty());
            CHECK(d.size() == 0u);
        }
        {
            Dict<int, int> d;
            CHECK(d.count(0) == 0u);
            CHECK(!d.contains(0));
            d[0] = 1;
            CHECK(!d.empty());
            CHECK(d.size() == 1u);
            CHECK(d.count(0) == 1u);
            CHECK(d.contains(0));
            CHECK(d.at(0) == 1);
            CHECK(d[0] == 1);
            d[0] = 2;
            CHECK(d.size() == 1u);
            CHECK(d.count(0) == 1u);
            CHECK(d.contains(0));
            CHECK(d.count(1) == 0u);
            CHECK(!d.contains(1));
            CHECK(d.at(0) == 2);
            CHECK(d[0] == 2);
            d[1] = 3;
            CHECK(d.size() == 2u);
            CHECK(d.count(0) == 1u);
            CHECK(d.contains(0));
            CHECK(d.count(1) == 1u);
            CHECK(d.contains(1));
            CHECK(d.at(0) == 2);
            CHECK(d[0] == 2);
            CHECK(d.at(1) == 3);
            CHECK(d[1] == 3);
            std::size_t erased_count = d.erase(10);
            CHECK(erased_count == 0u);
            erased_count = d.erase(0);
            CHECK(erased_count == 1u);
            CHECK(d.size() == 1u);
            CHECK(d.count(0) == 0u);
            CHECK(!d.contains(0));
            CHECK(d.count(1) == 1u);
            CHECK(d.contains(1));
            CHECK(d.at(1) == 3);
            erased_count = d.erase(1);
            CHECK(erased_count == 1u);
            CHECK(d.empty());
        }
    }

    TEST_CASE("test_iterate_dict_order") {
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
            CHECK(k == ke);
            CHECK(v == ve);
            i++;
        }
    }

}
