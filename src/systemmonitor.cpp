#include "systemmonitor.h"

SystemMonitor::SystemMonitor(QObject *parent)
    : QObject(parent)
{
    Update();
}

void SystemMonitor::Update()
{
    // Update CPU information
    cpu.Update();
    
    // Update system information
    system.Update();
    
    // Update process list
    processes.clear();
    for (int pid : system.Pids()) {
        processes.emplace_back(pid);  // Process constructor already updates all information
    }
    
    // Sort processes by CPU utilization (descending)
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.CpuUtilization() > b.CpuUtilization();
              });
} 