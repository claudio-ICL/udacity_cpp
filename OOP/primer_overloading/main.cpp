#include "linalg.h"
#include <cassert>
#include <iostream>
#include <vector>
int main() {
  Matrix A = Matrix(2, 2, std::vector<float>{1, 0, 0, 1});
  A.print();
  A(0, 0) = 4; // call to float& Matrix::operator()(int,int)
  std::cout << "\n";
  A.print(0, 0);
  assert(A(0, 0) == 4); // call to float Matrix::operator()(int,int)cont
  std::cout << "\n\n";
  A.print();
  std::vector<float> x{1, 0};
  print(x);
  std::vector<float> y = A * x;
  print(y);
  std::cout << x * y;
  return 0;
}
