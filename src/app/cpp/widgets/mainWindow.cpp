#include "mainWindow.h"
#include "mainWidget.h"
#include "../levels.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new MainWidget(this);
    mainWidget->setParent(this);

    QMenu *fileMenu = menuBar()->addMenu("File");
    level1Action = new QAction();
    level1Action->setText("Load Level 1");
    connect(level1Action, &QAction::triggered, this, &MainWindow::loadLevel1);
    level2Action = new QAction();
    level2Action->setText("Load Level 2");
    connect(level2Action, &QAction::triggered, this, &MainWindow::loadLevel2);
    level3Action = new QAction();
    level3Action->setText("Load Level 3");
    connect(level3Action, &QAction::triggered, this, &MainWindow::loadLevel3);
    fileMenu->addAction(level1Action);
    fileMenu->addAction(level2Action);
    fileMenu->addAction(level3Action);

    setCentralWidget(mainWidget);
    resize(700, 450);
    setWindowTitle("Rush Hour");
    setStatus("Loaded App");
    //setFixedSize(700, 450);
}

void MainWindow::loadLevel1()
{
    mainWidget->loadLevel(LEVEL_1_TEXT, "Level 1");
}

void MainWindow::loadLevel2()
{
    mainWidget->loadLevel(LEVEL_2_TEXT, "Level 2");
}

void MainWindow::loadLevel3()
{
    mainWidget->loadLevel(LEVEL_3_TEXT, "Level 3");
}