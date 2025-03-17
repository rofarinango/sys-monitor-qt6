#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTableWidget>
#include <QLabel>
#include "systemmonitor.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSystemInfo();

private:
    void setupUI();
    void createSystemInfoWidget();
    void createProcessTable();

    SystemMonitor *systemMonitor;
    QTimer *updateTimer;
    
    // System info widgets
    QLabel *cpuUsageLabel;
    QLabel *memoryUsageLabel;
    QLabel *uptimeLabel;
    QLabel *kernelLabel;
    QLabel *osLabel;
    
    // Process table
    QTableWidget *processTable;
};

#endif // MAINWINDOW_H 