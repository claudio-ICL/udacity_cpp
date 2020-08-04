#ifndef PROCESSOR_H
#define PROCESSOR_H
class Processor {
 public:
  float Utilization();

 private:
  int total_{0};
  int idle_{0};
};
#endif
