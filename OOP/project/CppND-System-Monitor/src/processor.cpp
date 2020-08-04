#include "processor.h"
#include <numeric>
#include <stdexcept>
#include <vector>
#include "linux_parser.h"
float Processor::Utilization() {  // Returns the aggregate CPU utilization
  std::vector<int> cpu;
  try {
    cpu = LinuxParser::ReadProcStat("cpu");
  } catch (std::invalid_argument&) {
    return 0.0f;
  }
  int idle = cpu[3] + cpu[4];
  int total = std::accumulate(cpu.begin(), cpu.end(), 0);
  int delta_total = total - total_;
  int delta_idle = idle - idle_;
  // utilization percentage in the time window between previous measurement of
  // the private variables total_ and idle_ and current function call, unless
  // total did not change, in which case overall utilization percentage since
  // boot
  float res = (delta_total != 0)
                  ? float(delta_total - delta_idle) / float(delta_total)
                  : float(total - idle) / float(total);
  // update the private variables total_ and idle_ with the current measurements
  total_ = total;
  idle_ = idle;
  return res;
}
