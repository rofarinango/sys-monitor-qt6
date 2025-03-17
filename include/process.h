#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
  Process(int pid); // Constructor
  int Pid() const;                               
  std::string User() const;                      
  std::string Command() const;                   
  float CpuUtilization() const;            
  std::string Ram() const;                       
  long int UpTime() const;                       
  bool operator<(Process const& a) const; 

private:
int processId_;
std::string user_;
std::string command_;
float cpuUsage_;
std::string ram_;
long upTime_;
enum ProcessCPUStates{
    kUTime_ = 0,
    kSTime_,
    kCuTime_,
    kCsTime_,
    kStartTime_
};

void getCpuUsage();
void getUser();
void getCommand();
void getRam();
void getUpTime();

};

#endif