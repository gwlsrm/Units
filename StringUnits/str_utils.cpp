// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "str_utils.h"

#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <optional>

#ifdef __BCPLUSPLUS__
#include <ctype.h>
#else
  #ifdef USE_BOOST
  #include <boost/algorithm/string.hpp>
  #endif
#endif // NEW_COMPILER

using namespace std;

std::string trim(const std::string& s)
{
    auto b_it = s.begin();
    auto e_it = s.end();
    // find new first position in string
    for (;b_it < s.end() && *b_it == ' '; ++b_it) {}
    if (b_it == e_it) return "";
    // find new last position in string
    for (e_it = s.end()-1; e_it >= b_it; --e_it) {
        if (*e_it != ' ' && *e_it != '\n' && *e_it != '\r') {
            break;
        }
    }
    e_it = e_it + 1;
    // return trimmed string
    return string(b_it, e_it);
}

std::string trim_right(const std::string& s) {
    auto b_it = s.begin();
    auto e_it = s.end();
    if (b_it == e_it) return "";
    // find new last position in string
    for (e_it = s.end()-1; e_it >= b_it; --e_it) {
        if (*e_it != ' ' && *e_it != '\n' && *e_it != '\r') {
            break;
        }
    }
    e_it = e_it + 1;
    // return trimmed string
    return string(b_it, e_it);
}

std::string_view strip(std::string_view line) {
    while (!line.empty() && isspace(line.front())) {
        line.remove_prefix(1);
    }
    while (!line.empty() && isspace(line.back())) {
        line.remove_suffix(1);
    }
    return line;
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

//std::string toLower(std::string s)
//{
//    for (size_t i = 0; i < s.size(); ++i) {
//        s[i] = tolower(s[i]);
//    }
//    return s;
//}

std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                // [](char c){ return std::tolower(c); }          // wrong
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

std::string str_toupper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::toupper(c); }
                  );
    return s;
}

bool startWith(const char* source, const char* signature)
{
  int n = int(strlen(signature));
  int i = 0;
  for(i = 0; i < n; i++)
    if(source[i] != signature[i]) break;
  return i == n ? true : false;
}

bool startWith(const std::string& source, const std::string& signature) {
    if (signature.size() > source.size()) return false;
    return source.compare(0, signature.size(), signature) == 0;
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

std::string intToStringF(int number, int digits) {
    stringstream ss;
    ss << setfill('0') << setw(digits);
    ss << number;
    return ss.str();
}

bool same_text(const std::string& s1, const std::string& s2)
{
#ifndef __BORLANDC__
    return str_tolower(s1) == str_tolower(s2);
#endif
}

void addSpacesToString(std::string& str, size_t new_length) {
  if (str.size() < new_length) {
    auto last_size = str.size();
    str.resize(new_length);
    for(size_t i = last_size; i < str.size(); i++) str[i] = ' ';
  }
}

std::vector<std::string> split_into_words(const std::string& str, char sep/*, bool is_grouped*/) {
    vector<string> result;
    string s = trim(str);
    auto str_begin = begin(s);
    const auto str_end = end(s);

    while (true) {
        auto it = find(str_begin, str_end, sep);
        result.emplace_back(str_begin, it);

        if (it == str_end) {
            break;
        } else {
            str_begin = next(it);
            while (str_begin != str_end && *str_begin == ' ') {
				++str_begin;
			}
			if (str_begin == str_end) {
                break;
			}
        }
    }
    return result;
}

std::pair<std::string_view, std::optional<std::string_view>> split_two_strict(std::string_view s, std::string_view delimiter) {
  const size_t pos = s.find(delimiter);
  if (pos == std::string_view::npos) {
    return {s, nullopt};
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
  string res;
  size_t full_size = accumulate(begin(strings), end(strings), 0u,
                              [](size_t b, const string& s) {return b + s.size() + 1u;});
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

void print_strings(std::ostream& out, const std::vector<std::string>& strings, char sep, char end_symbol) {
    bool is_first = true;
    for (const auto& s : strings) {
        if (is_first) {
            is_first = false;
        } else {
            out << sep;
        }
        out << s;
    }
    out << end_symbol;
}

std::string intToStringF(int i, int width) {
    string res = to_string(i);
    if ((int)res.size() < width) {
        res = string(width - res.size(), '0') + res;
    }
    return res;
}

//int word_count(const string& s, const set<char>& delimeters)
//{
//    size_t i(0);
//    int res(0);
//    while (i < s.size()) {
//        // delimeters before word
//        while (i < s.size() && delimeters.find(s[i]) != delimeters.end()) ++i;
//        // word
//        if (i < s.size()) ++res;
//        // word symbols
//        while (i < s.size() && delimeters.find(s[i]) == delimeters.end()) ++i;
//    }
//    return res;
//}
//
//int word_position(int n, const string& s, const set<char>& delimeters)
//{
//    int cnt(0);
//    size_t i(0);
//    while (i < s.size() && cnt != n) {
//        // skip over delimeters
//        while (i < s.size() && delimeters.find(s[i]) != delimeters.end()) ++i;
//        // if we're not beyond end of s, we're at the start of a word
//        if (i < s.size()) ++cnt;
//        // if not finished, find the end of the current word
//        if (cnt != n) {
//            while (i < s.size() && delimeters.find(s[i]) == delimeters.end()) ++i;
//        } else {
//            return i;
//        }
//    }
//    return -1;
//}
//
//std::string extract_word(int wordNum, const std::string& s, const std::set<char>& delimeters)
//{
//    int i = word_position(wordNum, s, delimeters);
//    unsigned int len(i);
//    if (i != -1) {
//        // find the end of current word
//        while (len < s.size() && delimeters.find(s[len]) == delimeters.end())
//            ++len;
//        return s.substr(i, len-i);
//    }
//    return "";
//}
//
//std::string extract_word(int wordNum, const std::string& s,
//                         const std::string& delimeters)
//{
//    #ifdef USE_BOOST
//    using namespace boost;
//    vector<string> words;
//    split(words, s, is_any_of(delimeters), token_compress_on);
//    if (static_cast<int>(words.size()) > wordNum)
//        return words[wordNum];
//    else
//    #endif // USE_BOOST
//        return "";
//}
