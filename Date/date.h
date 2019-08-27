#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <stdexcept>

class Date {
public:
  Date(int new_year, int new_month, int new_day);

  // getters and setters
  int getYear() const   {return year;}
  int getMonth() const  {return month;}
  int getDay() const    {return day;}
  // compare operators
  friend bool operator<(const Date& lhs, const Date& rhs);
  friend bool operator<=(const Date& lhs, const Date& rhs);
  friend bool operator>(const Date& lhs, const Date& rhs);
  friend bool operator>=(const Date& lhs, const Date& rhs);
  friend bool operator==(const Date& lhs, const Date& rhs);
  friend bool operator!=(const Date& lhs, const Date& rhs);
  // convert functions
  std::string asString(char sep = '-') const;
private:
  int year;
  int month;
  int day;
  static bool isValidDate(int aYear, int aMonth, int aDay);
  static bool isLeapYear(int aYear);
  static int dayInMonth(int aMonth, int aYear);
};

std::ostream& operator<<(std::ostream& stream, const Date& date);

Date parseDate(const std::string& date);
Date parseDate(std::istream& date_stream);

#endif /* DATE_H_ */
