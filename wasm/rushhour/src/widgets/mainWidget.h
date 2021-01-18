#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../common.h"

// forward declarations
class LevelWidget;
class BoardWidget;
class MainWindow;
class SquareWidget;

const std::string DEFAULT_LEVEL_TEXT = "..AA..\n.XX.B.\n....B.\n.DCCC.\n.D....\n.EE...\n";

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
};

#endif