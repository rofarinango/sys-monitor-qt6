#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization() const;
  void Update();

  Processor();
 private:
 mutable float prevTotalCpuTime;
 mutable float prevIdleCpuTime;

 vector<long> convertToLong(vector<string> values) const;
};

#endif