#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();
  std::vector<int>& Pids();
  std::map<int, Process>& Processes();
  void UpdateProcesses();
  void SortProcesses();
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel();
  std::string OperatingSystem();

 private:
  Processor cpu_ = {};
  std::vector<int> pids_;
  std::map<int, Process> processes_ = {};
  std::string kernel_;
  std::string os_;
};

#endif
