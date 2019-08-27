// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "metrologic_round.h"
#include "math_lib.h"
#include "UStrUtils_gw.h"

using namespace std;

int findPowerNum(double v) {
#ifndef __BORLANDC__
    v = fabs(v);
    string s = toStringF(v);
    size_t dot_pos = s.find('.');
    if (dot_pos == string::npos || dot_pos > 1) {    // integer value or xyz.abc value
        if (dot_pos != string::npos) s = s.substr(0, dot_pos);
        if (s[0] == '2' || s[0] == '1')
            return s.size()-2;
        else
            return s.size()-1;
    }
    else if (dot_pos == 1 && s[0] != '0') {         // x.y
        if (s[0] == '2' || s[0] == '1')
            return -1;
        else
            return 0;
    }
    else {
        int fs = -1;
        for (unsigned int i=0; i<s.size(); ++i) {
            if (s[i] != '0' && s[i] != '.') {
                fs = i;
                break;
            }
        }
        if (fs == -1) return s.size();
        if (s[fs] == '2' || s[fs] == '1')
            return -fs;
        else
            return 1-fs;
    }
    return 0;
#endif
}

std::string metrologic_round(double value, double dvalue)
{
    int n = findPowerNum(dvalue);
    value = roundTo(value, n);
    return toStringF(value, TFloatFormat::ffGeneral, 10);
}

std::string metrologic_round(double dvalue) {
    int n = findPowerNum(dvalue);
    dvalue = roundTo(dvalue, n);
    return toStringF(dvalue, TFloatFormat::ffGeneral, 10);
}
