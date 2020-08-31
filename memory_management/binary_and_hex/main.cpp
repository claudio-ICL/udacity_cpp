#include "ascii.h"
#include "conversion.h"
#include <iostream>
#include <vector>
int main() {
  std::vector<int> base{2, 10, 16};
  std::vector<int> num{1, 2, 3, 4, 7, 9, 10,};
  std::vector<int> den{16};
  for (auto b : base)
    for (auto p : num)
      for (auto q : den) {
        std::cout << std::endl;
        std::cout << "p=" << p << std::endl;
        std::cout << "q=" << q << std::endl;
        std::cout << "b=" << b << std::endl;
        std::cout << "floating point representation of p/q in base b: "
                  << Conversion::rational(p, q, b);
        std::cout << std::endl;
      }
  std::vector<int> numbers{1, 2, 10, 11, 12,  16, 31, 32, 55, 56, };
  for (auto b : base)
    for (auto n : numbers) {
      std::cout << std::endl;
      std::cout << "x=" << n << std::endl;
      std::cout << "b=" << b << std::endl;
      std::cout << "Representation of x in base b: "
                << Conversion::integer(n, b);
      std::cout << std::endl;
    }
  std::cout << "\n\nAscii table" << std::endl;
  Ascii table = Ascii();
  std::cout << "32: " << table[32] << std::endl;
  std::cout << "38: "  << table[38] << std::endl;
  std::cout << "A: " << table['A'] << std::endl;
  std::cout << "A: " << table('A') << std::endl;
  std::cout << "B: " << table['B'] << std::endl;
  std::cout << "B: " << table('B') << std::endl;
  return 0;
}
