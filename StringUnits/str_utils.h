#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <typeinfo>
#include <vector>

namespace gwstr {

/// remove spaces from left and right
std::string_view strip(std::string_view line);
/// remove spaces from left
std::string_view lstrip(std::string_view line);
/// remove spaces from right
std::string_view rstrip(std::string_view line);
/// remove spaces from begin and end
std::string trim(const std::string& s);
/// remove spaces from begin
std::string trim_left(const std::string& s);
/// remove spaces from the end
std::string trim_right(const std::string& s);
/// trim_right for c-string: it removes blanks from the end
void removeblanks(char* str);

/// converts string to lower: can be used with move for parameter
std::string str_tolower(std::string s);
/// converts string to upper
std::string str_toupper(std::string s);

/// returns true if string starts with signature (C-strings)
bool starts_with(const char* source, const char* signature);
/// returns true if string starts with signature (std::strings)
bool starts_with(const std::string& source, const std::string& signature);
/// returns true if string starts with signature (std::strings)
bool starts_with(std::string_view source, std::string_view signature);
/// returns true if string ends with signature (std::strings)
bool ends_with(const std::string& source, const std::string& signature);
/// returns true if string ends with signature (std::strings)
bool ends_with(std::string_view source, std::string_view signature);
/// case insensitive compare
bool same_text(const std::string& s1, const std::string& s2);
/// add spaces to the end of string to new length
void ljust(std::string& str, std::size_t new_length, char fillchar=' ');

// convert from and to string
// from string
/// from string to integer with default. don't throw exceptions
int strToIntDef(const std::string& str, int defValue);
/// from string to double with default. don't throw exceptions
double strToFloatDef(const std::string& str, double defValue);
/// converts from string to integer value (parameter). If success returns true. Don't throw exceptions
bool tryStrToInt(const std::string& str, int& value);
/// converts from string to double value (parameter). If success returns true. Don't throw exceptions
bool tryStrToFloat(const std::string& str, double& value);
struct bad_from_string : std::bad_cast  // class for transform error
{
	const char* what() const throw() { // override bad_cast's what
        return "bad cast from string";
    }
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
/// int -> string, if string size < width, zeros will be added to str begin
std::string intToStringF(int i, int width);

/// split words from string using separator
std::vector<std::string> split_into_words(const std::string& str, char sep = ' ');
/// reads next token from string and returns rest part of string as string_view
std::string_view readToken(std::string_view& s, std::string_view delimiter = " ");
/// join string to the one big string (seems to be more effective than '+')
std::string join_strings(const std::vector<std::string>& strings, char sep = ' ');
std::string join_strings(const std::vector<std::string>& strings, std::string_view sep);

/// true if all characters in string are digits
bool isdigit_s(std::string_view s);
/// true if all characters in string are letters
bool isalpha_s(std::string_view s);
/// true if all characters in string are letters or digits
bool isalnum_s(std::string_view s);
/// true if all characters in string are uppercase
bool isupper_s(std::string_view s);
/// true if all characters in string are lowercase
bool islower_s(std::string_view s);


// print some strings
template <typename T>
void print_vector(std::ostream& out, const std::vector<T>& values,
                  char sep = '\t', char end_symbol = '\n') {
    bool is_first = true;
    for (const auto& v : values) {
        if (is_first) {
            is_first = false;
        } else {
            out << sep;
        }
        out << v;
    }
    out << end_symbol;
}

} // namespace gwstr
