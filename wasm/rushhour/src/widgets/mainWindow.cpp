#include "mainWindow.h"
#include "mainWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new MainWidget(this);
    mainWidget->setParent(this);

    setCentralWidget(mainWidget);
    resize(700, 450);
    setWindowTitle("Rush Hour");
    setStatus("Loaded App");
    setFixedSize(700, 450);
}