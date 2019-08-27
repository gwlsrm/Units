#ifndef PARAM_STR_UTILS_H_INCLUDED
#define PARAM_STR_UTILS_H_INCLUDED

#include <string>

std::string readParam(int argc, char *argv[], int param_num, const std::string& defValue);
std::string getAllParamString(int argc, char *argv[]);

#endif // PARAM_STR_UTILS_H_INCLUDED
