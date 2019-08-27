// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "str_utils_unit_tests.h"
#include "UStrUtils_gw.h"
#include "test_runner.h"
#include <string>
#include <vector>

using namespace std;

void TestSplitIntoWords() {
    {
        string str = "a1 a2 a3";
        auto res = split_into_words(str);
        vector<string> expected = {"a1", "a2", "a3"};
        ASSERT_EQUAL(res, expected);
    }
    {
        string str = " a1 a2 a3";
        auto res = split_into_words(str);
        vector<string> expected = {"a1", "a2", "a3"};
        ASSERT_EQUAL(res, expected);
    }
    {
        string str = "a1 a2 a3 ";
        auto res = split_into_words(str);
        vector<string> expected = {"a1", "a2", "a3"};
        ASSERT_EQUAL(res, expected);
    }
}
