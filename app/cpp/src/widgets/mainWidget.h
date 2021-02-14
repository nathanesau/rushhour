#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "widgets.h"
#include "../common.h"

// forward declarations
class LevelWidget;
class BoardWidget;
class MainWindow;
class SquareWidget;

class MainWidget : public QWidget
{
    LevelWidget *levelWidget;
    BoardWidget *boardWidget;
    QHBoxLayout *levelLayout;
    QHBoxLayout *boardLayout;
    QHBoxLayout *mainLayout;
    MainWindow *mainWindow;

public:
    MainWidget(MainWindow *mainWindow, QWidget *parent = nullptr);

    void onEditBtn();

    void onApplyBtn();

    void onSquareClicked(SquareWidget *square);

    void keyReleaseEvent(QKeyEvent *event);

    void loadLevel(std::string levelText, std::string levelName);
};

#endif