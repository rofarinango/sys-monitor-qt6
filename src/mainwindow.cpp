#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , systemMonitor(new SystemMonitor(this))
    , updateTimer(new QTimer(this))
{
    setupUI();
    
    // Set up update timer
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateSystemInfo);
    updateTimer->start(1000); // Update every second
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Create system info section
    createSystemInfoWidget();
    
    // Create process table
    createProcessTable();
    
    // Set window properties
    setWindowTitle("System Monitor");
    resize(800, 600);
}

void MainWindow::createSystemInfoWidget()
{
    QWidget *infoWidget = new QWidget(this);
    QHBoxLayout *infoLayout = new QHBoxLayout(infoWidget);
    
    // Create labels for system information
    cpuUsageLabel = new QLabel("CPU Usage: 0%", this);
    memoryUsageLabel = new QLabel("Memory Usage: 0%", this);
    uptimeLabel = new QLabel("Uptime: 0:00:00", this);
    kernelLabel = new QLabel("Kernel: ", this);
    osLabel = new QLabel("OS: ", this);
    
    // Add widgets to layout
    infoLayout->addWidget(cpuUsageLabel);
    infoLayout->addWidget(memoryUsageLabel);
    infoLayout->addWidget(uptimeLabel);
    infoLayout->addWidget(kernelLabel);
    infoLayout->addWidget(osLabel);
    
    // Add stretch to push widgets to the left
    infoLayout->addStretch();
    
    centralWidget()->layout()->addWidget(infoWidget);
}

void MainWindow::createProcessTable()
{
    processTable = new QTableWidget(this);
    processTable->setColumnCount(5);
    processTable->setHorizontalHeaderLabels({"PID", "User", "CPU%", "Memory%", "Command"});
    processTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    centralWidget()->layout()->addWidget(processTable);
}

void MainWindow::updateSystemInfo()
{
    // Update system information
    systemMonitor->Update();  // Update all system information first
    cpuUsageLabel->setText(QString("CPU Usage: %1%").arg(systemMonitor->Cpu().Utilization() * 100.0f, 0, 'f', 1));
    memoryUsageLabel->setText(QString("Memory Usage: %1%").arg(systemMonitor->MemoryUtilization() * 100.0f, 0, 'f', 1));
    uptimeLabel->setText(QString("Uptime: %1").arg(QString::fromStdString(systemMonitor->UpTime())));
    kernelLabel->setText(QString("Kernel: %1").arg(QString::fromStdString(systemMonitor->GetSystem().Kernel())));
    osLabel->setText(QString("OS: %1").arg(QString::fromStdString(systemMonitor->GetSystem().OperatingSystem())));
    
    // Update process table
    const auto& processes = systemMonitor->Processes();
    processTable->setRowCount(processes.size());
    
    for (size_t i = 0; i < processes.size(); ++i) {
        const auto& process = processes[i];
        
        processTable->setItem(i, 0, new QTableWidgetItem(QString::number(process.Pid())));
        processTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(process.User())));
        processTable->setItem(i, 2, new QTableWidgetItem(QString::number(process.CpuUtilization())));
        processTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(process.Ram())));
        processTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(process.Command())));
    }
} 