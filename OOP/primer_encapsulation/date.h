class Date {
public:
  Date(int day, int month, int year);
  int Day() const { return day; }
  void Day(int day);
  int Month() const { return month; }
  void Month(int month);
  int Year() const { return year; }
  void Year(int year);
  int DaysInMonth();
  bool IsLeapYear();
  void print();

private:
  int day{1};
  int month{1};
  int year{0};
};
