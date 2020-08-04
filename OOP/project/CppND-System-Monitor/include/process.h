#ifndef PROCESS_H
#define PROCESS_H
#include <map>
#include <stdexcept>
#include <string>
class Process {
 public:
  Process(const int&);
  int Pid() const;
  static std::map<int, std::string> usermap;
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  void UpdateCpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator>(const Process& a) const;

 private:
  std::string user_;
  std::string command_;
  const int pid_;
  float cpu_utilization_;
};
#endif
