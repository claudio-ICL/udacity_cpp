#include "my_funs.h"
#include <iostream>
int main() {
  /*
  int i=1;
  int j=2;
  int k=i+j;
  print_lvalref(i);
  print_lvalref(k);
  print_rvalref(i+j);
  print_rvalref(std::move(k));
  */
  MyClass obj;
  obj = create_myclass(10);
  std::cout << "\n\nReached return in main\n";
  return 0;
}
