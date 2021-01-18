#pragma once

#include "../common.h"
#include "../controllers/rushHour.h"

class BoardWidget : public QWidget
{
private:
    QLabel *instructionLabel;
    std::vector<std::vector<SquareWidget *>> squares;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    std::map<std::string, std::string> carSelected;

public:
    Board(QWidget *parent = nullptr) : QWidget(parent)
    {
        // data
        carSelected.clear();

        // widgets
        instructionLabel = new QLabel("Use arrow keys to move cars");

        for (int i = 0; i < 6; i++)
        {
            squares.push_back(std::vector<SquareWidget*>(6));
            for (int j = 0; j < 6; j++)
            {
                squares[i][j] = new SquareWidget(i, j);
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
        mainLayout->addWidget(instructionLabel);
        mainLayout->addLayout(gridLayout);

        setLayout(mainLayout);
    }

    void renderLevel(const std::vector<std::vector<char>> &level,
                     const std::vector<std::map<std::string, std::string>> &cars)
    {
        // clear selection
        carSelected.clear();

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                squares[i][j]->setText(level[i][j]);
                if (cars.find(level[i][j]) != cars.end())
                {
                    auto car = cars[level[i][j]];
                    // style = f'background: {car["color"]}; border: 3px solid black;'
                    std::string style = "";
                    squares[i][j]->setStyleSheet(style);
                }
                else
                {
                    squares[i][j]->setStyleSheet("border: 3px solid black;")
                }
            }
        }
    }

    void onSquareClicked(SquareWidget *square)
    {
        parent()->onSquareClicked(square);
    }

    void selectCar(const std::map<std::string, std::string> &car)
    {
        if (carSelected.isEmpty())
        {
            // unselect previous car
            for (auto square : carSelected["squares"])
            {
                squares[square.first][square.second]->updateAlpha(255);
            }
        }

        // select new car
        for (auto square : carSelected["squares"])
        {
            squares[square.first][square.second]->updateAlpha(50);
        }

        carSelected = car;
    }

    /**
     * @brief moves a car up, left, down or right one square
     * 
     * @param board [['.', '.', 'A', 'A', '.', '.'], ...]
     * @param key "Up", "Down", "Left" or "Right"
     */
    void moveSelectedCar(const std::vector<std::vector<char>> &board, std::string key)
    {
        std::vector<std::vector<char>> init_board = board;

        auto controller = RushHour(board);
        char carName = carSelected["name"];
        int dir = (key == "Up") ? RushHour::UP : (key == "Down") ? RushHour::DOWN : (key == "Left") ? RushHour::LEFT : (key == "Right") ? RushHour::RIGHT;

        controller.makeMove(carName, dir, 1);

        return init_board != board;
    }
};