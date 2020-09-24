#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <string>
#include <chrono>
std::string read_mode(std::launch mode){
  return (mode==std::launch::async)? "async" : "deferred";
}
void print_info(int nLoops, int nThreads, std::launch mode){
    std::cout << "nLoops=" << nLoops << "; nThreads= " << nThreads;
    std::cout << "; mode: " << read_mode(mode) << std::endl;
}
void workerFunction(int n)
{
    // perform work
    for (int i = 0; i < n; ++i)  sqrt(12345.6789);
}
std::vector<std::future<void>> execute(int nLoops, int nThreads, std::launch mode){
    std::vector<std::future<void>> futures;
    for (int i = 0; i < nThreads; ++i)
    {
        futures.emplace_back(std::async(mode, workerFunction, nLoops));
    }
    return futures;
}
long measure(int nLoops, int nThreads, std::launch mode){
    // start time measurement
    auto t1 = std::chrono::high_resolution_clock::now();
    auto futures = std::move(execute(nLoops, nThreads, mode));
    // wait for tasks to complete
    for (const std::future<void> &ftr : futures)
        ftr.wait();
    // stop time measurement and print execution time
    auto t2 = std::chrono::high_resolution_clock::now();
    long /*std::chrono::microseconds */ duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    print_info(nLoops, nThreads, mode);
    std::cout << "run time: "<<  duration <<" microseconds\n" << std::endl;
    return duration;
}
void compare(int nLoops, int nThreads){
    bool parallel_gain = measure(nLoops, nThreads, std::launch::async) < measure (nLoops, nThreads, std::launch::deferred);
    std::cout << "nLoops= "<< nLoops << ", nThreads= " << nThreads <<":";
    std::cout << " Parallel execution " << (parallel_gain?"provided ":"did not provide ")<< "a speed up \n"<< std::endl;
}
int main()
{
    compare(10,10);
    compare(1e7,10);
    return 0;
}
