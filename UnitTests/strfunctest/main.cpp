// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <iostream>
#include <string>
#include <set>
#include "str_utils.h"
#include "gwstrTests.h"
#include <cassert>

using namespace std;

template <class T> string res_as_string(const T& test, const T& right_res)
{
    if (test == right_res)
        return "passed";
    else
        return "failed";
}

int main()
{
    TestAllStrUtils();
    return 0;
}
