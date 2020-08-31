#include <iostream>
//MyClass will hold the pointer _myInt with shared copy policy, i.e. all instances of MyClass will have the same pointer pointing to the same memory address and the number of such instances will be kept track of by the static variable _cnt

class MyClass
{
private:
    int *_myInt;
    static int _cnt;

public:
    MyClass(int val);
    ~MyClass();
    MyClass(MyClass &source);
};

int MyClass::_cnt = 0;

MyClass::MyClass(int val)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = val;
    ++_cnt;
    std::cout << "resource allocated at address " << _myInt << std::endl;
}

MyClass::~MyClass()
{
    --_cnt;
    if (_cnt == 0)
    {
        free(_myInt);
        std::cout << "resource freed at address " << _myInt << std::endl;
    }
    else
    {
        std::cout << "instance at address " << this << " goes out of scope with _cnt = " << _cnt << std::endl;
    }
}

MyClass::MyClass(MyClass &source)
{
    _myInt = source._myInt;
    ++_cnt;
    std::cout << _cnt << " instances with handles to address " << _myInt << " with _myInt = " << *_myInt << std::endl;
}

int main()
{
    MyClass source(42);
    MyClass destination1(source);
    MyClass destination2(source);
    MyClass destination3(source);

    return 0;
}
