#pragma once
#include <future>
#include<chrono>
template<typename R>
bool is_ready(std::future<R> const &f){
  return f.wait_for(std::chrono::milliseconds(0))==std::future_status::ready;
}
