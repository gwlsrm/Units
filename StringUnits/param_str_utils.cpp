// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "param_str_utils.h"

using namespace std;

std::string readParam(int argc, char *argv[], int param_num, const std::string& defValue) {
    if (param_num > argc) {
        return defValue;
    }
    return argv[param_num];
}

std::string getAllParamString(int argc, char *argv[]) {
    string res;
    for (int i = 1; i < argc; ++i) {
        res += argv[i];
        res += " ";
    }
    return res;
}
