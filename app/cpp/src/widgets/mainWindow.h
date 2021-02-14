#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgets.h"
#include "../common.h"

// forward declarations
class MainWidget;

class MainWindow : public QMainWindow
{
    MainWidget *mainWidget;

    QAction *level1Action;
    QAction *level2Action;
    QAction *level3Action;

public:
    MainWindow(QWidget *parent = nullptr);

    void setStatus(std::string status)
    {
        statusBar()->showMessage(QString::fromStdString(status));
    }

    void loadLevel1();

    void loadLevel2();

    void loadLevel3();
};

#endif