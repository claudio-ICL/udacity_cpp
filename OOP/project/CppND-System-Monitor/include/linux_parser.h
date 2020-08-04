#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <filesystem>
#include <fstream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include "process.h"
namespace fs = std::filesystem;

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
std::string OperatingSystem();
std::string Kernel();
float MemoryUtilization();  // Returns percentage of used memory
long UpTime();              // Returns uptime in seconds
int TotalProcesses();       // Returns total number of processes
int RunningProcesses();     // Returns number of running processes
std::vector<int> Pids();
std::vector<int> ReadProcStat(const std::string&);
std::map<int, std::string> Usermap();

// Processes
std::string Command(const int& pid);
int Ram(const int& pid);
int Uid(const int& pid);
long int UpTime(const int& pid);
long int StartTime(const int& pid);
long int CPU_TotalTime(const int& pid);
long ProcessStat(const int&, int);
int ProcessStatus(const int&, const std::string&);
std::vector<long> ProcessStat(const int&, std::vector<int>);
};  // namespace LinuxParser

#endif
