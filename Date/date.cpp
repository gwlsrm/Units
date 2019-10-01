// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <vector>
#include <tuple>
#include <sstream>
#include <iomanip>
#include "date.h"

using namespace std;

Date::Date(int new_year, int new_month, int new_day)
	: year(new_year), month(new_month), day(new_day)
{
    if (!isValidDate(new_year, new_month, new_day)) {
        throw logic_error("Invalid date: ");
    };
}

bool Date::isValidDate(int aYear, int aMonth, int aDay)
{
    if (aMonth > 12 || aMonth < 1) {
      return false;
    }
    if (aDay < 1 || aDay > dayInMonth(aMonth, aYear)) {
      return false;
    }
    return true;
}

bool Date::isLeapYear(int aYear) {
    return ((aYear % 4 == 0 && aYear % 100 != 0) || aYear % 400);
}

int Date::dayInMonth(int aMonth, int aYear) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(aYear)) {
        days[1] = 29;
    }
    return days[aMonth-1];
}

std::string Date::asString(char sep) const {
    stringstream stream;
    stream << *this;
    return stream.str();
}

bool operator<(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) <
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) <=
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator>(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) >
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) >=
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) ==
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) !=
		   tie(rhs.year, rhs.month, rhs.day);
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.getYear() <<
      '-' << setw(2) << setfill('0') << date.getMonth() <<
      '-' << setw(2) << setfill('0') << date.getDay();
  return stream;
}

Date parseDate(const std::string& date) {
  istringstream date_stream(date);
  return parseDate(date_stream);
}

Date parseDate(std::istream& date_stream) {
	  bool ok = true;

	  int year;
	  ok = ok && (date_stream >> year);
	  ok = ok && (date_stream.peek() == '-');
	  date_stream.ignore(1);

	  int month;
	  ok = ok && (date_stream >> month);
	  ok = ok && (date_stream.peek() == '-');
	  date_stream.ignore(1);

	  int day;
	  ok = ok && (date_stream >> day);
	  ok = ok && (date_stream.eof() || date_stream.peek() == ' ' || date_stream.peek() == '\n'
			  || date_stream.peek() == '\t');

	  if (!ok) {
	    //throw logic_error("Wrong date format: ");
		  cerr << "Wrong date format: " << endl;
		  return Date(-1, 1, 1);
	  }
	  return Date(year, month, day);
}


