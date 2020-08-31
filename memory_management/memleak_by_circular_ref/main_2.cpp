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
  std::shared_ptr<MyClass> obj = std::make_shared<MyClass>();
  delete obj.get();
  // If line 15 is commented out, behaviour is as expected i.e.
  // obj_1->~MyClass() is not called when exiting this scope
  std::shared_ptr<MyClass> obj_1(new MyClass);
  // obj.get() == obj_1.get(), or in other words obj->this == obj_1->this
  obj_1->_ptr = obj_1; // Setting circular reference
  return 0;
  // Upon exiting this scope, we do not expect obj_1->~MyClass() to be called
  // because of the circular reference. Instead, because of line 15, it is
  // actually called.
}
