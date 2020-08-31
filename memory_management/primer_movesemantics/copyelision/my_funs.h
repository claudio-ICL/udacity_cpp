#pragma once
#include<stdlib.h>
void print_lvalref(int &);
void print_rvalref(int &&);
class MyClass{
  private:
    int size_;
    int* data_;
  public:
    MyClass(size_t s=0, bool verbose=true); //constructor
    ~MyClass(); //destructor
    MyClass(const MyClass &source); //copy constructor
    MyClass(MyClass &&source); //move constructor
    MyClass &operator=(const MyClass &source); //copy assignment operator
    MyClass &operator=(MyClass &&source); //move assignment operator
};
MyClass create_myclass(size_t); //outofscope constructor
