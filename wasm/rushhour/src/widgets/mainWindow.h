#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../common.h"

// forward declarations
class MainWidget;

class MainWindow : public QMainWindow
{
    MainWidget *mainWidget;

public:
    MainWindow(QWidget *parent = nullptr);

    void setStatus(std::string status)
    {
        statusBar()->showMessage(QString::fromStdString(status));
    }
};

#endif