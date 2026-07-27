#include "str_utils.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <optional>

#ifdef USE_BOOST
#include <boost/algorithm/string.hpp>
#endif

namespace gwstr {

std::string_view strip(std::string_view line) {
    while (!line.empty() && isspace(line.front())) {
        line.remove_prefix(1);
    }
    while (!line.empty() && isspace(line.back())) {
        line.remove_suffix(1);
    }
    return line;
}

std::string_view lstrip(std::string_view line) {
    while (!line.empty() && isspace(line.front())) {
        line.remove_prefix(1);
    }
    return line;
}

std::string_view rstrip(std::string_view line) {
    while (!line.empty() && isspace(line.back())) {
        line.remove_suffix(1);
    }
    return line;
}

std::string trim(const std::string& s)
{
    return std::string(strip(std::string_view(s)));
}

std::string trim_left(const std::string& s) {
    return std::string(lstrip(std::string_view(s)));
}

std::string trim_right(const std::string& s) {
    return std::string(rstrip(std::string_view(s)));
}

void removeblanks(char* str)
{
  int n = int(strlen(str)) - 1;
  for(int i = n; i >= 0; --i)
    if(str[i] != ' ') {
      str[i+1] = 0;
      return;
    }
  str[0] = 0;
}

std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); } // don't work with char
                  );
    return s;
}

std::string str_toupper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::toupper(c); }
                  );
    return s;
}

bool starts_with(const char* source, const char* signature)
{
    int sig_len = int(strlen(signature));
    if (int(strlen(source)) < sig_len) return false;
    for (int i = 0; i < sig_len; i++)
        if (source[i] != signature[i]) return false;
    return true;
}

bool starts_with(const std::string& source, const std::string& signature) {
    if (signature.size() > source.size()) return false;
    return source.compare(0, signature.size(), signature) == 0;
}

bool starts_with(std::string_view source, std::string_view signature) {
    if (signature.size() > source.size()) return false;
    return source.compare(0, signature.size(), signature) == 0;
}

bool ends_with(const std::string& source, const std::string& signature) {
    if (signature.size() > source.size()) return false;
    return source.compare(
        source.size() - signature.size(),
        std::string::npos,
        signature) == 0;
}

bool ends_with(std::string_view source, std::string_view signature) {
    if (signature.size() > source.size()) return false;
    return source.compare(
        source.size() - signature.size(),
        std::string::npos,
        signature) == 0;
}

int strToIntDef(const std::string& str, int defValue){
    try {
        int res = stol(str);
        return res;
    } catch (std::invalid_argument&) {
        return defValue;
    }
}

double strToFloatDef(const std::string& str, double defValue) {
    try {
        double res = stod(str);
        return res;
    } catch (std::invalid_argument&) {
        return defValue;
    }
}

bool tryStrToInt(const std::string& str, int& value) {
    try {
        value = stol(str);
        return true;
    } catch (std::invalid_argument&) {
        return false;
    }
}

bool tryStrToFloat(const std::string& str, double& value) {
    try {
        value = stod(str);
        return true;
    } catch (std::invalid_argument&) {
        return false;
    }
}

std::string intToStringF_need_to_test(int number, int digits) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(digits);
    ss << number;
    return ss.str();
}

std::string intToStringF(int i, int width) {
    std::string res = std::to_string(i);
    if ((int)res.size() < width) {
        res = std::string(width - res.size(), '0') + res;
    }
    return res;
}

bool same_text(const std::string& s1, const std::string& s2)
{
    return str_tolower(s1) == str_tolower(s2);
}

void ljust(std::string& str, size_t new_length, char fillchar) {
    if (str.size() < new_length) {
        str.resize(new_length, fillchar);
    }
}

std::vector<std::string> split_into_words(const std::string& str, char sep) {
    std::vector<std::string> result;
    std::string_view s(str);
    std::string sep_s(1, sep);
    while (!s.empty()) {
        auto token = strip(readToken(s, sep_s));
        // ignore empty tokens (appears if str has consecutive spaces)
        if (token.empty()) continue;
        result.emplace_back(token);
    }
    return result;
}

std::pair<std::string_view, std::optional<std::string_view>> split_two_strict(std::string_view s, std::string_view delimiter) {
  const size_t pos = s.find(delimiter);
  if (pos == std::string_view::npos) {
    return {s, std::nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

std::pair<std::string_view, std::string_view> split_two(std::string_view s, std::string_view delimiter) {
  const auto [lhs, rhs_opt] = split_two_strict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

std::string_view readToken(std::string_view& s, std::string_view delimiter) {
  const auto [lhs, rhs] = split_two(s, delimiter);
  s = rhs;
  return lhs;
}

std::string join_strings(const std::vector<std::string>& strings, char sep) {
    if (strings.empty()) return "";
    // calc final string size
    size_t full_size = accumulate(begin(strings), end(strings), size_t{0},
                              [](size_t b, const std::string& s) {return b + s.size();});
    full_size += strings.size() - 1;
    // make string
    std::string res;
    res.reserve(full_size);
    bool is_first = true;
    for (const auto& s : strings) {
        if (is_first) {
            is_first = false;
        } else {
            res += sep;
        }
        res += s;
    }
    return res;
}

std::string join_strings(const std::vector<std::string>& strings, std::string_view sep) {
    if (strings.empty()) return "";
    // calc final string size
    size_t full_size = accumulate(begin(strings), end(strings), 0u,
                                  [](size_t b, const std::string& s) {return b + s.size();});
    full_size += (strings.size() - 1) * sep.size();
    // make string
    std::string res;
    res.reserve(full_size);
    bool is_first = true;
    for (const auto& s : strings) {
        if (is_first) {
            is_first = false;
        } else {
            res += sep;
        }
        res += s;
    }
    return res;
}

bool isdigit_s(std::string_view s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isalpha_s(std::string_view s) {
    return std::all_of(s.begin(), s.end(), ::isalpha);
}

bool isalnum_s(std::string_view s) {
    return std::all_of(s.begin(), s.end(), ::isalnum);
}

bool isupper_s(std::string_view s) {
    return std::all_of(s.begin(), s.end(), ::isupper);
}

bool islower_s(std::string_view s) {
    return std::all_of(s.begin(), s.end(), ::islower);
}

} // namespace gwstr
