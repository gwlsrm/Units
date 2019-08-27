//---------------------------------------------------------------------------
#pragma once

#include <string>
#include <set>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string_view>

// remove spaces, compare
std::string trim(const std::string& s);
std::string trim_right(const std::string& s);
void removeblanks(char* str);
[[deprecated]] std::string toLower(std::string s);
std::string str_tolower(std::string s);
std::string str_toupper(std::string s);
bool startWith(const char* source, const char* signature);
bool startWith(const std::string& source, const std::string& signature);
bool same_text(const std::string& s1, const std::string& s2);
void addSpacesToString(std::string& str, std::size_t new_length);

// convert from and to string
// from string
int strToIntDef(const std::string& str, int defValue);
double strToFloatDef(const std::string& str, double defValue);
bool tryStrToInt(const std::string& str, int& value);
bool tryStrToFloat(const std::string& str, double& value);
struct bad_from_string : std::bad_cast  // class for transform error
{
#ifndef __BORLANDC__
	const char* what() const throw() { // override bad_cast's what
        return "bad cast from string";
    }
#endif
};
template<class T>
T from_string(const std::string& s)
{
	std::istringstream is(s);
	T t;
	if (!(is >> t)) throw bad_from_string();
	return t;
}
// to string
enum class TFloatFormat {ffGeneral, ffExponent, ffFixed};
template<class T> std::string toStringF(const T& value, TFloatFormat float_format = TFloatFormat::ffGeneral,
                                        int precision = -1)
{
    std::ostringstream os;
    // set float format
    switch (float_format) {
    case TFloatFormat::ffExponent:
        os << std::scientific;
        break;
    case TFloatFormat::ffFixed:
        os << std::fixed;
        break;
    default:
        break;
    }
    // print with setprecision
    if (precision == -1)
        os << value;
    else
        os << std::setprecision(precision) << value;
    return os.str();
}

// split words from string
std::vector<std::string> split_into_words(const std::string& str, char sep = ' ', bool is_grouped = false);
std::string_view readToken(std::string_view& s, std::string_view delimiter = " ");
//int word_count(const std::string& s, const std::set<char>& delimeters);
//std::string extract_word(int wordNum, const std::string& s,
//                         const std::set<char>& delimeters);
//std::string extract_word(int wordNum, const std::string& s,
//                         const std::string& delimeters);

std::string join_strings(const std::vector<std::string>& strings, char sep = ' ');

// print some strings
void print_strings(std::ostream& out, const std::vector<std::string>& strings, char sep = '\t', char end_symbol = '\n');
