#pragma once

#include "../common.h"

class MainWindow : public QMainWindow
{
    MainWidget *mainWidget;

public:
    MainWindow(QWidget *parent = nullptr) :
        QMainWindow(parent)
    {
        mainWidget = new MainWidget;
        mainWidget-setParent(this);

        setCentralWidget(mainWidget);
        resize(700, 450);
        setWindowTitle("Rush Hour");
        setStatus("Loaded App");
        setFixedSize(700, 450);
    }

    void setStatus(std::string status)
    {
        statusBar().showMessage(status);
    }
}