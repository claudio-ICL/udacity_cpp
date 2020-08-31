#include <stdlib.h>
#include <iostream>

class MyClass
{
private:
    int *_number;

public:
    MyClass()
    {
        std::cout << "Allocate memory\n";
        _number = (int *)malloc(sizeof(int));
    }
    ~MyClass()
    {
        std::cout << "Delete memory\n";
        free(_number);
    }
    void setNumber(int number)
    {
        *_number = number;
        std::cout << "_number: " << _number << "\n";
        std::cout << "*_number: " << *_number << "\n";
    }
};


int main()
{
    // allocate memory using malloc
    // comment these lines out to run the example below
    /*
    MyClass *myClass = (MyClass *)malloc(sizeof(MyClass)); //Constructor is not called, so memory at address _number is not allocated
    myClass->setNumber(42); // EXC_BAD_ACCESS (segmentation fault)
    free(myClass); //Destructor is not called, so memory at address _number is not freed
    */
	  
	// allocate memory using new
    MyClass *myClass = new MyClass();//Constructor is called, so memory at address _number is allocated
    myClass->setNumber(42); // works as expected
    delete myClass;//Destructor is called, so memory at address _number is freed


    return 0;
}
