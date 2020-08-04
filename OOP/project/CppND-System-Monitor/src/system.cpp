#include "system.h"
#include <algorithm>

System::System() {
  kernel_ = LinuxParser::Kernel();
  os_ = LinuxParser::OperatingSystem();
  cpu_ = Processor();
  UpdateProcesses();
}
Processor& System::Cpu() { return cpu_; }
void System::UpdateProcesses() {
  pids_ = LinuxParser::Pids();
  for (int& pid : pids_) {
    // If pid is not in the map "processes_", then a new object "Process"
    // with the corresponding pid  is added to "processes_".
    if (processes_.find(pid) == processes_.end()) {
      try {
        processes_.insert({pid, Process(pid)});
      } catch (...) {
      }
    }
  }
  for (auto process = processes_.begin(); process != processes_.end();) {
    // If pid of process is no longer associated to a directory in /proc/, we
    // erase it from the map "processes_". Otherwise, we update the cpu
    // utilization of the process.
    if (std::find(pids_.begin(), pids_.end(), process->first) == pids_.end())
      try {
        process = processes_.erase(process);
      } catch (...) {
        process++;
      }
    else {
      try {
        process++->second.UpdateCpuUtilization();
      } catch (...) {
        process++;
      }
    }
  }
  SortProcesses();
}
void System::SortProcesses() {
  // The sorted list of processes is stored in the private
  // member vector<int> pid_.
  // The function NCurseDisplay::DisplayProcesses will read the first n pids
  // from this vector and it will access the corresponding processes by reading
  // from the container std::map<int, Process> processes_.
  std::sort(pids_.begin(), pids_.end(), [&](int& a, int& b) {
    if (!(processes_.find(a) == processes_.end()))
      if (!(processes_.find(b) == processes_.end()))
        return processes_.at(a) > processes_.at(b);
      else {
        return true;
      }
    else {
      return false;
    }
  });
}
std::map<int, Process>& System::Processes() { return processes_; }
std::vector<int>& System::Pids() { return pids_; }
std::string System::Kernel() { return kernel_; }
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }
std::string System::OperatingSystem() { return os_; }
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }
long int System::UpTime() { return LinuxParser::UpTime(); }
