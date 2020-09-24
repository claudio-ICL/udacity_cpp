#include <iostream>
#include <memory>
class MyClass {
public:
  std::shared_ptr<MyClass> _ptr;
  MyClass() {
    std::cout << "Constructing MyClass at memory address " << this << std::endl;
  }
  ~MyClass() {
    std::cout << "Destructing MyClass at memory address " << this << std::endl;
  }
};
int main() {
  std::shared_ptr<MyClass> obj_1(new MyClass);
  obj_1->_ptr = obj_1; // Setting circular reference
  return 0;
}
