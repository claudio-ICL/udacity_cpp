#include "process.h"
#include "linux_parser.h"
using std::string;

std::map<int, string> Process::usermap{LinuxParser::Usermap()};
Process::Process(const int& pid) : pid_(pid) {
  try {
    user_ = usermap.at(LinuxParser::Uid(pid));
  } catch (std::out_of_range&) {
    user_ = "??";
  }
  command_ = LinuxParser::Command(pid);
  UpdateCpuUtilization();
}
string Process::User() const { return user_; }
string Process::Command() const { return command_; }
int Process::Pid() const { return pid_; }
float Process::CpuUtilization() const { return cpu_utilization_; }
void Process::UpdateCpuUtilization() {
  cpu_utilization_ = float(LinuxParser::CPU_TotalTime(pid_)) / float(UpTime());
}
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }
string Process::Ram() {
  int kB = LinuxParser::Ram(pid_);
  return std::to_string(float(kB) / 1000) + " MB";
}
bool Process::operator>(const Process& a) const {
  return CpuUtilization() > a.CpuUtilization();
}
