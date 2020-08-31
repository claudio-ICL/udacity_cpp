#include "my_funs.h"
#include <iostream>
void print_lvalref(int &val) {
  std::cout << "print_rvalref: val=" << val << ";   &val=" << &val << std::endl;
}
void print_rvalref(int &&val) {
  std::cout << "print_rvalref: val=" << val << ";   &val=" << &val << std::endl;
}
MyClass::MyClass(size_t s, bool verbose) {
  size_ = s;
  data_ = new int[size_];
  if (verbose) {
    std::cout << "Creating instance of MyClass at memory address " << this
              << ".  ";
    std::cout << "size_=" << size_ << ";    data_=" << data_ << std::endl;
  }
}
MyClass::~MyClass() {
  std::cout << "Destructing instance of MyClass at memory address " << this
            << ".  ";
  if (data_ != nullptr) {
    delete[] data_;
    std::cout << "Freeing memory address " << data_;
  }
  std::cout << std::endl;
}
MyClass::MyClass(const MyClass &source) { // deep copy
  size_ = source.size_;
  data_ = new int[size_];
  if (source.data_ != nullptr)
    *data_ = *(source.data_);
  std::cout << "Instanciating MyClass at memory address " << this
            << " as a deep copy of the instance at " << &source << ".   ";
  std::cout << "size_=" << size_ << ";    data_=" << data_ << std::endl;
}
MyClass::MyClass(MyClass &&source) {
  size_ = source.size_;
  data_ = source.data_;
  source.size_ = 0;       // invalidate source's member size_
  source.data_ = nullptr; // Invalidate source's member data_
  std::cout << "Instanciating MyClass at memory address " << this
            << " by moving from rvalue reference at " << &source << ".   ";
  std::cout << "size_=" << size_ << ";    data_=" << data_ << std::endl;
}
MyClass &MyClass::operator=(const MyClass &source) {
  if (this != &source) { // protection against self assignment
    delete[] data_;
    size_ = source.size_;
    data_ = new int[size_];
    if (source.data_ != nullptr)
      *data_ = *(source.data_);
    std::cout << "Assigning MyClass at memory address " << this
              << " as a deep copy of the instance at " << &source << ".   ";
    std::cout << "size_=" << size_ << ";    data_=" << data_ << std::endl;
  }
  return *this;
  // Destructor of source will be called upon return
}
MyClass &MyClass::operator=(MyClass &&source) {
  if (this != &source) {
    delete[] data_;
    size_ = source.size_;
    data_ = source.data_;
    source.size_ = 0;       // invalidate source's member size_
    source.data_ = nullptr; // Invalidate source's member data_
    std::cout << "Assigning to MyClass at memory address " << this
              << " by moving from rvalue reference at memory address "
              << &source << ".   ";
    std::cout << "size_=" << size_ << ";    data_=" << data_ << std::endl;
  }
  return *this;
  // Destructor of source will be called upon return
}
MyClass create_myclass(size_t s) {
  std::cout << "Call to create_myclass:   ";
  return MyClass(s, true);
}
