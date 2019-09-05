#ifndef PARAM_STR_UTILS_H_INCLUDED
#define PARAM_STR_UTILS_H_INCLUDED

#include <string>

/// return n-th param or default value
std::string readParam(int argc, char *argv[], int param_num, const std::string& defValue);
/// form all params to one single string (can be used for logging)
std::string getAllParamString(int argc, char *argv[]);

#endif // PARAM_STR_UTILS_H_INCLUDED
