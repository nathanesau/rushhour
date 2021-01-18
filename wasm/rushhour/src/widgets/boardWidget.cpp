#include "boardWidget.h"
#include "mainWidget.h"
#include "squareWidget.h"
#include "../controllers/rushHour.h"

BoardWidget::BoardWidget(MainWidget *mainWidget, QWidget *parent) :
    mainWidget(mainWidget),
    QWidget(parent)
{
    // data
    carSelected.clear();

    // widgets
    for (int i = 0; i < 6; i++)
    {
        squares.push_back(std::vector<SquareWidget*>(6));
        for (int j = 0; j < 6; j++)
        {
            squares[i][j] = new SquareWidget(i, j, this);
        }
    }

    // layouts
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            gridLayout->addWidget(squares[i][j], i, j);
        }
    }

    mainLayout = new QVBoxLayout();
    //mainLayout->addWidget(instructionLabel);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);
}

const Car &BoardWidget::getCarSelected()
{
    return carSelected;
}

void BoardWidget::setCarSelected(const Car &pCarSelected)
{
    carSelected = pCarSelected;
}

void BoardWidget::renderLevel(const std::vector<std::vector<char>> &level,
                              const std::map<char, Car> &cars)
{
    // clear selection
    carSelected.clear();

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            squares[i][j]->setText(QString::fromStdString(std::string(1, level[i][j])));
            if (cars.find(level[i][j]) != cars.end())
            {
                auto carName = level[i][j];
                auto car = cars.find(carName)->second;
                std::string style = "background: " + car.color + "; border: 3px solid black;";
                squares[i][j]->setStyleSheet(QString::fromStdString(style));
            }
            else
            {
                squares[i][j]->setStyleSheet("border: 3px solid black;");
            }
        }
    }
}

void BoardWidget::onSquareClicked(SquareWidget *square)
{
    mainWidget->onSquareClicked(square);
}

void BoardWidget::selectCar(const Car &car)
{
    // unselect previous car
    for (auto square : carSelected.squares)
    {
        squares[square.first][square.second]->updateAlpha(255);
    }

    // select new car
    for (auto square : car.squares)
    {
        squares[square.first][square.second]->updateAlpha(50);
    }

    carSelected = car;
}

bool BoardWidget::moveSelectedCar(std::vector<std::vector<char>> &board, std::string key)
{
    std::vector<std::vector<char>> init_board = board;

    auto controller = RushHour(board);
    char carName = carSelected.name;
    int dir = (key == "Up") ? RushHour::UP : (key == "Down") ? RushHour::DOWN : (key == "Left") ? 
        RushHour::LEFT : (key == "Right") ? RushHour::RIGHT : -1;

    controller.makeMove(carName, dir, 1);

    return init_board != board;
}