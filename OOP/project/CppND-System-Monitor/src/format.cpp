#include "format.h"
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long secs) {
  std::stringstream res;
  for (int d : std::vector<int>{3600, 60, 1}) {
    res << std::setw(2) << std::setfill('0') << (secs / d)
        << (d == 1 ? "" : ":");
    secs = secs % d;
  }
  return res.str();
}
