#include<cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>
#include "check_future_status.h"

std::mutex mtxcout;

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getID() { return _id; }
    void drive() {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::microseconds(std::rand()/1000));
        _arrived=true;
    }

private:
    int _id;
    bool _arrived{false};
};

class WaitingVehicles
{
public:
    WaitingVehicles() : _numVehicles(0) {}

    int getNumVehicles() 
    { 
        std::lock_guard<std::mutex> uLock(_mutex);
        return _numVehicles; 
    }

    bool dataIsAvailable()
    {
        std::lock_guard<std::mutex> myLock(_mutex);
        return !_vehicles.empty();
    }

    Vehicle popBack()
    {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::microseconds(std::rand()/1000));
        // perform vector modification under the lock
        std::unique_lock<std::mutex> lock(_mutex);
        _cond.wait(lock, [this](){return !_vehicles.empty();});

        // remove last vector element from queue
        Vehicle v = std::move(_vehicles.back());
        _vehicles.pop_back();
        --_numVehicles;

        return v; // will not be copied due to return value optimization (RVO) in C++
    }

    void pushBack(Vehicle &&v)
    {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::microseconds(std::rand()/1000));
        {std::lock_guard<std::mutex> lock(mtxcout);
        std::cout << "   Vehicle #" << v.getID() << " is being added to the queue" << std::endl;
        }
        {
        // perform vector modification under the lock
        std::lock_guard<std::mutex> lock(_mutex);
        _vehicles.emplace_back(std::move(v));
        ++_numVehicles;
        _cond.notify_one();
        }
    }

private:
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
    std::mutex _mutex;
    int _numVehicles;
    std::condition_variable _cond;
};

int main()
{
    using Ms = std::chrono::milliseconds;
    using mus = std::chrono::microseconds;
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }
    auto active = [&futures](){
      for (auto it = futures.begin(); it!=futures.end(); ++it){
        if (!is_ready(*it))  return true;
        }
      return false;
    };
    while (active()||queue->dataIsAvailable())
    {
      /*
       {std::lock_guard<std::mutex> lock(mtxcout);
        std::cout <<"Entering while"<< std::endl;
        std::cout << queue->getNumVehicles() << " vehicle(s) left in the queue" << std::endl;
       }
       */
        if (queue->dataIsAvailable())
        {
            Vehicle v = queue->popBack();
            {std::lock_guard<std::mutex> lock(mtxcout);
            std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
            }

        }
    }

    std::cout << "Finished : " << queue->getNumVehicles() << " vehicle(s) left in the queue" << std::endl;

    return 0;
}
