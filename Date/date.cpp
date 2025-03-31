#include <vector>
#include <tuple>
#include <sstream>
#include <iomanip>
#include "date.h"


Date::Date(int new_year, int new_month, int new_day)
	: year(new_year), month(new_month), day(new_day)
{
    if (!isValidDate(new_year, new_month, new_day)) {
        throw std::logic_error("Invalid date: ");
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
    std::stringstream stream;
    stream << *this;
    return stream.str();
}

bool operator<(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) <
		   std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) <=
		   std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator>(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) >
		   std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) >=
		   std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) ==
		   std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) !=
		   std::tie(rhs.year, rhs.month, rhs.day);
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
  stream << std::setw(4) << std::setfill('0') << date.getYear() <<
      '-' << std::setw(2) << std::setfill('0') << date.getMonth() <<
      '-' << std::setw(2) << std::setfill('0') << date.getDay();
  return stream;
}

Date parseDate(const std::string& date) {
  std::istringstream date_stream(date);
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
	      std::cerr << "Wrong date format: " << std::endl;
		  return Date(-1, 1, 1);
	  }
	  return Date(year, month, day);
}
