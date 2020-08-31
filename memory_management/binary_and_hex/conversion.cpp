#include "conversion.h"
#include <cassert>

Conversion::Symbols::Symbols(int b) : base{b} {
  for (int n = 0; n < (b < 10 ? b : 10); n++) {
    hex.insert({n, char(48 + n)});
  }
  for (int n = 0; n < b - 10; n++) {
    hex.insert({10 + n, char(65 + n)});
  }
}
char Conversion::Symbols::operator[](int n) const { return hex.at(n); }

std::string Conversion::rational(unsigned int p, unsigned int q, unsigned int b,
                                 int max_digits) {
  assert(p < q);
  Conversion::Symbols symbols = Symbols(b);
  std::map<int, int> ps;
  int pos{0};
  std::string res;
  while ((ps.find(p) == ps.end()) /*&&(pos<=max_digits)*/) {
    int pb = p * b;
    res.push_back(symbols[pb / q]);
    ps.insert({p, pos++});
    p = (pb) % q;
  }
  if (p != 0) {
    while (res.size() < max_digits) {
      res = res + res.substr(ps.at(p), res.size());
    }
  }
  return "0." + res.substr(0, max_digits);
}
std::string Conversion::integer(unsigned int n, unsigned int b) {
  if (n == 0)
    return 0;
  Conversion::Symbols symbols = Symbols(b);
  std::string res;
  while (n != 0) {
    res.insert(0, 1, symbols[n % b]);
    n = n / b;
  }
  return res;
}
