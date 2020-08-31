#pragma once
#include <map>
#include <string>
namespace Conversion {
class Symbols {
public:
  Symbols(int);
  char operator[](int) const;

private:
  std::map<int, char> hex;
  int base;
};
std::string rational(unsigned int p, unsigned int q, unsigned int b,
                     int max_digits = 10);
std::string integer(unsigned int n, unsigned int b);
}; // namespace Conversion
