#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include "../common.h"
#include "../car.h"

// forward declarations
class MainWidget;
class SquareWidget;

class BoardWidget : public QWidget
{
    std::vector<std::vector<SquareWidget *>> squares;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    Car carSelected;
    MainWidget *mainWidget;

public:
    BoardWidget(MainWidget *mainWidget, QWidget *parent = nullptr);

    const Car &getCarSelected();

    void setCarSelected(const Car &pCarSelected);

    void renderLevel(const std::vector<std::vector<char>> &level,
                     const std::map<char, Car> &cars);

    void onSquareClicked(SquareWidget *square);

    void selectCar(const Car &car);

    /**
     * @brief moves a car up, left, down or right one square
     * 
     * @param board [['.', '.', 'A', 'A', '.', '.'], ...]
     * @param key "Up", "Down", "Left" or "Right"
     * 
     * @return true if car was moved, false otherwise
     */
    bool moveSelectedCar(std::vector<std::vector<char>> &board, std::string key);
};

#endif