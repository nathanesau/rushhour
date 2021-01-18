#include "mainWidget.h"
#include "boardWidget.h"
#include "levelWidget.h"
#include "squareWidget.h"
#include "mainWindow.h"
#include "../controllers/rushHour.h"
#include "../utility/string.h"

MainWidget::MainWidget(MainWindow *mainWindow, QWidget *parent) :
    mainWindow(mainWindow), QWidget(parent)
{
    // widgets
    levelWidget = new LevelWidget(this);
    std::vector<std::vector<char>> level;
    auto lines = utility::split(DEFAULT_LEVEL_TEXT, "\n");
    for(auto line : lines) {
        std::vector<char> v(line.begin(), line.end());
        level.push_back(v);
    }
    levelWidget->setOriginalLevel(level);
    boardWidget = new BoardWidget(this);
    boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());

    // event handlers
    connect(levelWidget->getEditBtn(), &QAbstractButton::clicked, this, &MainWidget::onEditBtn);
    connect(levelWidget->getApplyBtn(), &QAbstractButton::clicked, this, &MainWidget::onApplyBtn);

    // layouts
    levelLayout = new QHBoxLayout;
    levelLayout->addWidget(levelWidget);
    boardLayout = new QHBoxLayout;
    boardLayout->addWidget(boardWidget);
    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(levelLayout, 40);
    mainLayout->addLayout(boardLayout, 60);

    setLayout(mainLayout);
}

void MainWidget::onSquareClicked(SquareWidget *square)
{
    // check to see if level editing is currently on
    if (!levelWidget->getOriginalBoardTE()->isReadOnly())
    {
        return;
    }

    int i = square->getRow();
    int j = square->getCol();
    auto car = levelWidget->getCars().find(levelWidget->getLevel()[i][j])->second;
    boardWidget->selectCar(car);
    std::string status = "Selected Car " + levelWidget->getLevel()[i][j];
    mainWindow->setStatus(status);
}

void MainWidget::onEditBtn()
{
    // make board editable
    levelWidget->getOriginalBoardTE()->setReadOnly(false);
    levelWidget->getOriginalBoardTE()->setStyleSheet("");
}

void MainWidget::onApplyBtn()
{
    // disable editing
    levelWidget->getOriginalBoardTE()->setReadOnly(true);
    levelWidget->getOriginalBoardTE()->setStyleSheet("background: lightgrey");

    auto levelText = levelWidget->getOriginalBoardTE()->toPlainText();
    bool valid = levelWidget->validateLevel(levelText.toStdString());

    if (valid)
    {
        // update board        
        std::vector<std::vector<char>> level;
        auto lines = utility::split(levelText.toStdString(), "\n");
        for(auto line : lines) {
            std::vector<char> v(line.begin(), line.end());
            level.push_back(v);
        }
        levelWidget->setOriginalLevel(level);
        levelWidget->parseLevel(level);
        boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());

        std::string status = "Board Change Detected";
        mainWindow->setStatus(status);
    }
    else
    {        
        std::string status = "Invalid Board Change Detected (not applied)";
        mainWindow->setStatus(status);
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    // check to see if level editing is currently on
    if (!levelWidget->getOriginalBoardTE()->isReadOnly())
    {
        return;
    }

    // check if a car is currently selected
    if (boardWidget->getCarSelected().name == '.')
    {
        return;
    }

    // the car we are trying to move
    char carName = boardWidget->getCarSelected().name;

    if (event->key() == Qt::Key_Up)
    {
        if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Up"))
        {
            levelWidget->setCurrentLevel(levelWidget->getLevel());
            boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
            boardWidget->setCarSelected(levelWidget->getCars()[carName]);
            std::string status = "Moved Car " + std::string(1, boardWidget->getCarSelected().name) + " Up";
            mainWindow->setStatus(status);
        }
    }
    else if (event->key() == Qt::Key_Down)
    {
        if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Down"))
        {
            levelWidget->setCurrentLevel(levelWidget->getLevel());
            boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
            boardWidget->setCarSelected(levelWidget->getCars()[carName]);
            std::string status = "Moved Car " + std::string(1, boardWidget->getCarSelected().name) + " Down";
            mainWindow->setStatus(status);
        }
    }
    else if (event->key() == Qt::Key_Left)
    {
        if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Left"))
        {
            levelWidget->setCurrentLevel(levelWidget->getLevel());
            boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
            boardWidget->setCarSelected(levelWidget->getCars()[carName]);
            std::string status = "Moved Car " + std::string(1, boardWidget->getCarSelected().name) + " Left";
            mainWindow->setStatus(status);
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Right"))
        {
            levelWidget->setCurrentLevel(levelWidget->getLevel());
            boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
            boardWidget->setCarSelected(levelWidget->getCars()[carName]);
            std::string status = "Moved Car " + std::string(1, boardWidget->getCarSelected().name) + " Right";
            mainWindow->setStatus(status);
        }
    }

    auto controller = RushHour(levelWidget->getLevel());
    if (controller.isSolved())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Notification");
        msgBox.setText("Congrats! You have solved the Rush Hour Puzzle!");
        msgBox.exec();
    }
}