#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QObject>
#include "processor.h"
#include "process.h"
#include "system.h"
#include "format.h"

class SystemMonitor : public QObject {
    Q_OBJECT

public:
    SystemMonitor(QObject *parent = nullptr);
    
    Processor& Cpu() { return cpu; }
    const Processor& Cpu() const { return cpu; }
    const std::vector<Process>& Processes() const { return processes; }
    float MemoryUtilization() const { return system.MemoryUtilization(); }
    std::string UpTime() const { return Format::ElapsedTime(system.UpTime()); }
    const System& GetSystem() const { return system; }
    
    void Update();

private:
    Processor cpu;
    System system;
    std::vector<Process> processes;
};

#endif // SYSTEMMONITOR_H 