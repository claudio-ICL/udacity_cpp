#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
std::string elapsed_time(long secs) {
  assert(secs < 24 * 3600);
  int d[3] = {3600, 60, 1};
  int time[3]{0, 0, 0};
  int *t = time;
  std::string res{"00 :00 :00 "};
  char *r = &(res[0]);
  std::for_each(d, d + 3, [&secs, &t, &r](int d) {
    *t = secs / d;
    secs = secs % d;
    snprintf(r, 3, "%02d", *(t++));
    r += 4;
  });
  return res;
}
int main() {
  for (long secs : std::vector<long>{
           0,
           1,
           10,
           60,
           120,
           180,
           3600,
           786,
           72400,
       })
    std::cout << secs << " seconds equal to (HH:MM:SS) " << elapsed_time(secs)
              << std::endl;
  return 0;
}
