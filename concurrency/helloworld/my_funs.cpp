#include"my_funs.h"
void my_fun(){
  std::thread::id id = std::this_thread::get_id();
  std::cout << "\nmy_fun has been called. Thread id: " << id << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "my_fun on thread " <<id<< " is now exiting" << std::endl;
}
