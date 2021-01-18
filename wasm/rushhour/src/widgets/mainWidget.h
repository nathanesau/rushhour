#include "../common.h"
#include "levelWidget.h"
#include "boardWidget.h"
#include "../controllers/rushHour.h"

const std::string DEFAULT_LEVEL_TEXT = "..AA..\n" +
                                       ".XX.B.\n" +
                                       "....B.\n" +
                                       ".DCCC.\n" +
                                       ".D....\n" +
                                       ".EE...\n";

class MainWidget : public QWidget
{
private:
    LevelWidget *levelWidget;
    BoardWidget *boardWidget;
    QHBoxLayout *levelLayout;
    QHBoxLayout *boardLayout;
    QHBoxLayout *mainLayout;

public:
    MainWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // widgets
        levelWidget = new LevelWidget(this);
        // level = [list(line) for line in DEFAULT_LEVEL_TEXT.splitlines() if line.strip()]
        // levelWidget.setOriginalLevel(level);
        boardWidget = new BoardWidget(this);
        boardWidget.renderLevel(levelWidget->getLevel(), levelWidget->getCars());

        // event handlers
        // levelWidget.editBtn.clicked.connect(self.onEditBtn)
        // levelWidget.applyBtn.clicked.connect(self.onApplyBtn)

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

    void onEditBtn()
    {
        // make board editable
        levelWidget->getOriginalBoardTE()->setReadOnly(false);
        levelWidget->getOriginalBoardTE()->setStyleSheet("");
    }

    void onApplyBtn()
    {
        // disable editing
        levelWidget->getOriginalBoardTE()->setReadOnly(True);
        levelWidget->getOriginalBoardTE()->setStyleSheet("background: lightgrey");

        auto levelText = levelWidget->getOriginalBoardTE()->toPlainText();
        bool valid = levelWidget->validateLevel(levelText);

        if (valid)
        {
            // update board
            // level = [list(line) for line in levelText.splitlines() if line.strip()]
            levelWidget->setOriginalLevel(level);
            levelWidget->parseLevel(level);
            boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());

            // status = f'Board Change Detected at {datetime.utcnow().strftime(("%m/%d/%Y, %H:%M:%s"))}'
            std::string status = "";
            parent()->setStatus(status);
        }
        else
        {
            // status = f'Invalid Board Change Detected at {datetime.utcnow().strftime("%m/%d/%Y, %H:%M:%S")} (board change not applied)'
            std::string status = "";
            parent->setStatus(status);
        }
    }

    void onSquareClicked(SquareWidget *square)
    {
        // check to see if level editing is currently on
        if (!levelWidget->getOriginalBoardTE()->isReadOnly())
        {
            return;
        }

        int i = square->getRow();
        int j = square->getCol();
        char car = levelWidget->getCars()[levelWidget->getLevel()[i][j]];
        boardWidget->selectCar(car);
        // status = f'Selected Car {self.levelWidget.level[i][j]}'
        std::string status = "";
        parent()->setStatus(status);
    }

    void keyReleaseEvent(QEvent *event)
    {
        // check to see if level editing is currently on
        if (!levelWidget->getOriginalBoardTE()->isReadOnly())
        {
            return;
        }

        // check if a car is currently selected
        if (!boardWidget->getCarSelected())
        {
            return;
        }

        // the car we are trying to move
        char carName = boardWidget->getCarSelected()["name"];

        if (event->key() == Qt::Key_Up)
        {
            if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Up"))
            {
                levelWidget->setCurrentLevel(levelWidget->getLevel());
                boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
                boardWidget->setCarSelected(levelWidget->getCars()[carName]);
                // status = f'Moved Car {self.boardWidget.carSelected["name"]} Up'
                std::string status = "";
                parent()->setStatus(status);
            }
        }
        else if (event->key() == Qt::Key_Down)
        {
            if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Down"))
            {
                levelWidget->setCurrentLevel(levelWidget->getLevel());
                boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
                boardWidget->setCarSelected(levelWidget->getCars()[carName]);
                // status = f'Moved Car {self.boardWidget.carSelected["name"]} Down'
                std::string status = "";
                parent()->setStatus(status);
            }
        }
        else if (event->key() == Qt::Key_Left)
        {
            if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Left"))
            {
                levelWidget->setCurrentLevel(levelWidget->getLevel());
                boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
                boardWidget->setCarSelected(levelWidget->getCars()[carName]);
                // status = f'Moved Car {self.boardWidget.carSelected["name"]} Left'
                std::string status = "";
                parent()->setStatus(status);
            }
        }
        else if (event->key() == Qt::Key_Right)
        {
            if (boardWidget->moveSelectedCar(levelWidget->getLevel(), "Right"))
            {
                levelWidget->setCurrentLevel(levelWidget->getLevel());
                boardWidget->renderLevel(levelWidget->getLevel(), levelWidget->getCars());
                boardWidget->setCarSelected(levelWidget->getCars()[carName]);
                // status = f'Moved Car {self.boardWidget.carSelected["name"]} Right'
                std::string status = "";
                parent()->setStatus(status);
            }
        }

        auto controller = RushHour(levelWidget->getLevel());
        if (controller->isSolved())
        {
            // msgBox = QMessageBox()
            // msgBox.setWindowTitle("Notification")
            // msgBox.setText("Congrats! You have solved the Rush Hour Puzzle!")
            // msgBox.exec()
        }
    }
};