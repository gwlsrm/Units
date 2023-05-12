#include "param_str_utils.h"

using namespace std;

std::string readParam(int argc, const char *argv[], int param_num, const std::string& defValue) {
    if (param_num > argc) {
        return defValue;
    }
    return argv[param_num];
}

std::string getAllParamString(int argc, const char *argv[]) {
    string res;
    for (int i = 1; i < argc; ++i) {
        res += argv[i];
        res += " ";
    }
    return res;
}
