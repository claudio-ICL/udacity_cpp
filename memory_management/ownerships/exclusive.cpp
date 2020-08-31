#include <iostream>
//MyClass will hold the pointer _myInt with exclusive copy, i.e. the pointer will be null except for the most recent initialised instance

class MyClass
{
private:
    int *_myInt;

public:
    MyClass()
    {
        _myInt = (int *)malloc(sizeof(int));
        std::cout << "resource allocated" << std::endl;
    }
    ~MyClass()
    {
        if (_myInt != nullptr)
        {
            free(_myInt);
            std::cout << "resource freed" << std::endl;
        }
            
    }
    MyClass(MyClass &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
    }
    MyClass &operator=(MyClass &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
        return *this;
    }
};

int main()
{
    MyClass source;
    MyClass destination(source);

    return 0;
}
