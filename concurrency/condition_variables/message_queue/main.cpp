#include "message_queue.h"
#include "check_future_status.h"
#include <iostream>
#include <thread>
#include <memory>
#include <algorithm>
std::mutex mtxcout;
int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<MessageQueue<int>> queue(new MessageQueue<int>);

    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i)
    {
        int message = i;
        futures.emplace_back(std::async(std::launch::async, &MessageQueue<int>::send, queue, std::move(message)));
    }

    auto active = [&futures](){
      for (auto it = futures.begin(); it!=futures.end(); ++it){
        if (!is_ready(*it))  return true;
        }
      return false;
    };
    while (active() || queue->not_empty())
    {
        int message = queue->receive();
        {std::lock_guard<std::mutex> lock(mtxcout);
        std::cout << "   Message #" << message << " has been removed from the queue" << std::endl;
        }
    }

    std::cout << "Finished!" << std::endl;

    return 0;
}
