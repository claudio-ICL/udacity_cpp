#include <iostream>
#include <memory>
class MyClass {
public:
  std::weak_ptr<MyClass> _ptr;
  MyClass() {
    std::cout << "Constructing MyClass at memory address " << this << std::endl;
  }
  ~MyClass() {
    std::cout << "Destructing MyClass at memory address " << this << std::endl;
  }
};
int main() {
  std::shared_ptr<MyClass> obj = std::make_shared<MyClass>();
  //delete obj.get();
  std::shared_ptr<MyClass> obj_1 = std::make_shared<MyClass>();
  obj_1->_ptr = obj_1; // Setting circular reference
  return 0;
  //The usage of weak_ptr breaks the circular reference, hence allowing the destructor obj_1->~MyClass() to be called when exiting this scope
}
