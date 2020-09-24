#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include<algorithm>
std::mutex cout_mutex;

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getId() {return _id;}

private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles() {}

    // getters / setters
    void printSize()
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "#vehicles = " << _vehicles.size() << std::endl;
    }

    // typical behaviour methods
    void pushBack(Vehicle &&v)
    {
        using Ms= std::chrono::milliseconds;
        int num_attempts = 3;
        int n=0;
        for (int n=0; n<num_attempts; ++n){
          bool acquired = _mutex.try_lock_for(Ms(50));
          if (acquired){
            std::this_thread::sleep_for(Ms(5)); //simulate work
            _vehicles.emplace_back(std::move(v)); // data race would cause an exception
            _mutex.unlock();
            break;
          }
          else{
            {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Vehicle " << v.getId() << " failed to be pushed back. Attempt # " << n+1 << std::endl;
            }
            std::this_thread::sleep_for(Ms(5));
          }
       }
    }

private:
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
    std::timed_mutex _mutex;
};

int main()
{
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles); 
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 1000; ++i)
    {
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    queue->printSize();

    return 0;
}

