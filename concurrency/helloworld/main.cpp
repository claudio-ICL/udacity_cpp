#include<iostream>
#include<thread>
#include"my_funs.h"
int main(){
    std::cout<<"Hello world of concurrency!\n";
    unsigned int num_cores = std::thread::hardware_concurrency();
    std::cout << "num_cores: " << num_cores << std::endl;
    std::cout << "main thread id: "<< std::this_thread::get_id() << std::endl;
    std::thread t(my_fun);
    std::cout << "main is now sleeping" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "\nmain is computing a sum: 2+3=" << 2+3 << std::endl;
    t.join();
    return 0;
}



