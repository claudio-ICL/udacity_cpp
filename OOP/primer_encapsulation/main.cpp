#include "date.h"
#include <iostream>
#include <vector>
int main() {
  for (int m = 1; m < 13; m++) {
    Date today = Date(1, m, 1998);
    today.print();
    std::cout << "DaysInMonth: " << today.DaysInMonth() << std::endl;
    std::cout << "\n";
  }
  for (int y : std::vector<int>{1900, 1998, 2000, 2001, 2004, 2099, 2100}) {
    Date today = Date(13, 1, y);
    today.print();
    std::cout << "IsLeapYear: " << today.IsLeapYear() << std::endl;
    std::cout << "\n";
  }
  for (int m = 1; m < 13; m++) {
    Date today = Date(1, m, 2000);
    today.print();
    std::cout << "IsLeapYear: " << today.IsLeapYear()
              << ";  DaysInMonth: " << today.DaysInMonth() << std::endl;
    std::cout << "\n";
  }
  return 0;
}
