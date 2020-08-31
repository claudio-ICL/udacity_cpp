#include "date.h"
#include <cassert>
#include <iostream>

Date::Date(int d, int m, int y) {
  Year(y);
  Month(m);
  Day(d);
}

void Date::Day(int d) {
  if (d >= 1 && d <= Date::DaysInMonth())
    this->day = d;
}

void Date::Month(int m) {
  if (m >= 1 && m <= 12)
    this->month = m;
}

void Date::Year(int y) { this->year = y; }

int Date::DaysInMonth() {
  int &m = this->month;
  if ((m + int(m > 7)) % 2 == 0) {
    if (m == 2) {
      return 28 + int(this->IsLeapYear());
    } else {
      return 30;
    }
  } else {
    return 31;
  }
}

bool Date::IsLeapYear() {
  int &y = this->year;
  return ((y % 4 == 0) && (y % 100 != 0)) | (y % 400 == 0);
}

void Date::print() {
  std::cout << this->Year() << "-" << this->Month() << "-" << this->Day()
            << std::endl;
}
