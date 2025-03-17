#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() {
    vector<Process> foundProcesses{};
    vector<int> processIds = LinuxParser::Pids();
    for(int processId : processIds){
        foundProcesses.emplace_back(processId);
    }

    //Cpu usage processes sort
    sort(foundProcesses.begin(), foundProcesses.end(), [](const Process& pA, const Process& pB){
        return (pB.CpuUtilization() < pA.CpuUtilization());
    });
    processes_ = foundProcesses;
    return processes_;
}

// Return the system's kernel identifier (string)
std::string System::Kernel() const { return LinuxParser::Kernel(); }

// Return the system's memory utilization
float System::MemoryUtilization() const { return LinuxParser::MemoryUtilization(); }

// Return the operating system name
std::string System::OperatingSystem() const { return LinuxParser::OperatingSystem(); }

// Return the number of processes actively running on the system
int System::RunningProcesses() const { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
int System::TotalProcesses() const { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long int System::UpTime() const { return LinuxParser::UpTime(); }

// Update system information
void System::Update() {
    // Update the processes list
    Processes();
}

// Return the list of process IDs
std::vector<int> System::Pids() const {
    return LinuxParser::Pids();
}