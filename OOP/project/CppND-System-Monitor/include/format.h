#ifndef FORMAT_H
#define FORMAT_H
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
namespace Format {
long constexpr max_duration{100 * 60 * 60};
std::string ElapsedTime(long times);
};  // namespace Format
#endif
