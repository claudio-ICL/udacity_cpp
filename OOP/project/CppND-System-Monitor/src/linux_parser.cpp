#include "linux_parser.h"
#include <dirent.h>
#include <unistd.h>
#include <cassert>
#include <stdexcept>
#include "process.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}
float LinuxParser::MemoryUtilization() {  // Returns percentage of used memory
  std::map<string, float> meminfo;
  float kB = 0.0f;
  string key;
  string line;
  std::ifstream infostream(kProcDirectory + kMeminfoFilename);
  if (infostream.is_open()) {
    while ((std::getline(infostream, line)) && (meminfo.size() < 2)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key;
      if ((key == "MemTotal") || (key == "MemFree")) {
        linestream >> kB;
        meminfo[key] = kB;
      }
    }
    return (meminfo["MemTotal"] - meminfo["MemFree"]) / meminfo["MemTotal"];
  }
  return 0.0f;  // In case "infostream" could not be opened
}
long LinuxParser::UpTime() {
  string line;
  long secs{0};
  std::ifstream proc_uptime(kProcDirectory + kUptimeFilename);
  if (proc_uptime.is_open()) {
    std::getline(proc_uptime, line);
    std::istringstream datastream(line);
    datastream >>
        secs;  // reads only the first number and converts it into "long"
  }
  return secs;
}
int LinuxParser::TotalProcesses() {  // Returns the total number of processes
  try {
    return LinuxParser::ReadProcStat("processes")[0];
  } catch (std::invalid_argument&) {
    return -1;  // In case reading fails
  }
}
int LinuxParser::RunningProcesses() {  // Returns the number of running
                                       // processes
  try {
    return LinuxParser::ReadProcStat("procs_running")[0];
  } catch (std::invalid_argument&) {
    return -1;  // In case reading fails
  }
}
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  for (auto& elem : fs::directory_iterator(kProcDirectory)) {
    if (elem.is_directory()) {
      string dirname = elem.path().filename();
      if (std::all_of(dirname.begin(), dirname.end(), isdigit))
        pids.push_back(stoi(dirname));
    }
  }
  return pids;
}
// Reads from /proc/stat the line identified by "key" and returns the numeric
// data found on this line as a vector of ints.
std::vector<int> LinuxParser::ReadProcStat(const string& key) {
  string line;
  string item;
  bool found{false};
  int data{0};
  std::vector<int> res;
  std::ifstream proc_stat(kProcDirectory + kStatFilename);
  if (proc_stat.is_open()) {
    while (getline(proc_stat, line)) {
      std::istringstream datastream(line);
      datastream >> item;
      if (key == item) {
        found = true;
        while (datastream >> data) res.push_back(data);
        return res;
      }
    }
    proc_stat.close();
  }
  if (!found)
    throw std::invalid_argument("Specified key not found in " + kProcDirectory +
                                kStatFilename);
  return res;
}
// Reads from /etc/passwd and returns a container that associates Uid and
// username
std::map<int, string> LinuxParser::Usermap() {
  std::map<int, string> usermap;
  int key{0};  // "key" is the int that stores "Uid"
  string line;
  string value;  // "value" is the string that stores the username
  string x;
  std::ifstream passwd(kPasswordPath);
  if (passwd.is_open()) {
    while (getline(passwd, line)) {
      // The following is an example of how 'line' starts:
      // root:x:0
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream datastream(line);
      datastream >> value >> x >> key;
      usermap.insert({key, value});
    }
    passwd.close();
  }
  return usermap;
}

// Returns the command associated with the process identified by [pid]
string LinuxParser::Command(const int& pid) {
  std::ifstream pid_cmdline(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string cmdline;
  if (pid_cmdline.is_open()) getline(pid_cmdline, cmdline);
  pid_cmdline.close();
  return cmdline;
}
int LinuxParser::Ram(const int& pid) {  // Returns the memory used by the
                                        // process identified by [pid]
  try {
    return LinuxParser::ProcessStatus(pid, "VmSize");
  } catch (std::invalid_argument&) {
    return 0;
  }
}
// I am removing the following signature:
// string LinuxParser::User(int pid) { return string(); }
// Indeed, it is LinuxParser::Usermap that builds the correspondence between Uid
// and username. The container std::map<int, string> usermap_ will be stored
// as a static element of the class Process.
// Therefore there is no need to parse for user, but, once
// Uid has been parsed, the corresponding username is obtained by reading the
// map. See Process::Process(const int&) and Process::usermap.
// This has the advantage that /etc/passwd is read only once.
int LinuxParser::Uid(
    const int& pid) {  // Returns the Uid of the process identified by [pid]
  try {
    return LinuxParser::ProcessStatus(pid, "Uid");
  } catch (std::invalid_argument&) {
    return 0;
  }
}
// Returns the uptime of a process in seconds, computed as the difference
// between the uptime of the system and the starttime of the process
long int LinuxParser::UpTime(const int& pid) {
  return UpTime() - StartTime(pid);
}
long int LinuxParser::StartTime(
    const int& pid) {  // Returns starttime in seconds
  // The 22nd entry in the file /proc/[pid]/stat corresponds to starttime.
  // See https://man7.org/linux/man-pages/man5/proc.5.html
  return ProcessStat(pid, 22) / sysconf(_SC_CLK_TCK);
}
long int LinuxParser::CPU_TotalTime(
    const int& pid) {  // Returns totaltime in seconds
  // The 14th and the 15th entries in the
  // file /proc/[pid]/stat correspond to cpu time spent in
  // user code and in kernel code.
  // The 16th and the 17th entries in the file
  // /proc/[pid]/stat correrspond to waited-for-children analogue cpu times.
  // See https://man7.org/linux/man-pages/man5/proc.5.html
  vector<long> cpu_time = ProcessStat(pid, vector<int>{14, 15, /* 16, 17*/});
  return std::accumulate(cpu_time.begin(), cpu_time.end(), 0) /
         sysconf(_SC_CLK_TCK);
}
long LinuxParser::ProcessStat(const int& pid, int item) {
  return ProcessStat(pid, vector<int>{item})[0];
}
// Reads from /proc/[pid]/status the line identified by "key" and returns the
// numeric data found on this line as an int
int LinuxParser::ProcessStatus(const int& pid, const string& key) {
  string line;
  string item;
  bool found{false};
  int res{0};
  std::ifstream pid_status(kProcDirectory + to_string(pid) + kStatusFilename);
  if (pid_status.is_open()) {
    while (getline(pid_status, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream datastream(line);
      datastream >> item;
      if (key == item) {
        found = true;
        datastream >> res;
        return res;
      }
    }
    pid_status.close();
  }
  if (!found)
    throw std::invalid_argument("Specified key not found in " + kProcDirectory +
                                to_string(pid) + kStatusFilename);
  return res;
}
// Reads from /proc/[pid]/stat and returns the numeric data found in the
// positions given by 'items'
vector<long> LinuxParser::ProcessStat(const int& pid, vector<int> items) {
  vector<long> data;
  string d;
  string line;
  std::ifstream pid_stat(kProcDirectory + to_string(pid) + kStatFilename);
  if (pid_stat.is_open()) {
    getline(pid_stat, line);
    std::istringstream datastream(line);
    int id{0};
    datastream >> id;
    assert(id == pid);  // Check consistent pid
    for (int i : items) {
      datastream.seekg(0);
      for (int j = 1; j <= i; j++) {
        datastream >> d;
      }
      data.push_back(std::stol(d));
    }
  }
  return data;
}
