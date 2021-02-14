#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include "../common.h"
#include "../car.h"

const std::vector<std::string> COLORS = {
    "rgba(0, 128, 0, 255)",   // green
    "rgba(0, 0, 255, 255)",   // blue
    "rgba(0, 255, 255, 255)", // cyan
    "rgba(255, 255, 0, 255)", // yellow
    "rgba(128, 0, 128, 255)", // purple
    "rgba(255, 0, 255, 255)", // magenta
    "rgba(128, 0, 0, 255)",   // maroon
    "rgba(0, 255, 0, 255)",   // lime
    "rgba(0, 128, 128)"       // teal
};

class LevelWidget : public QWidget
{
    std::vector<std::vector<char>> level;
    std::map<char, Car> cars;

    QPushButton *editBtn;
    QPushButton *applyBtn;
    QLabel *originalBoardLabel;
    QLabel *currentBoardLabel;
    QTextEdit *originalBoardTE;
    QTextEdit *currentBoardTE;
    QHBoxLayout *menuLayout;
    QVBoxLayout *mainLayout;

public:
    LevelWidget(QWidget *parent = nullptr);

    std::vector<std::vector<char>> &getLevel()
    {
        return level;
    }

    std::map<char, Car> &getCars()
    {
        return cars;
    }

    QPushButton *getEditBtn()
    {
        return editBtn;
    }

    QPushButton *getApplyBtn()
    {
        return applyBtn;
    }

    QTextEdit *getOriginalBoardTE()
    {
        return originalBoardTE;
    }

    QTextEdit *getCurrentBoardTE()
    {
        return currentBoardTE;
    }

    /**
     * @brief sets level and cars using provided level.
     * 
     * @param pLevel provided level.
     */
    void parseLevel(std::vector<std::vector<char>> pLevel);

    /**
     * @brief check whether the provided level is valid or not.
     * 
     * @param levelText level as a string which can be parsed to 2D array of char.
     * 
     * @return true if level valid, false otherwise.
     */
    bool validateLevel(std::string levelText);

    void setOriginalLevel(std::vector<std::vector<char>> level);

    void setCurrentLevel(std::vector<std::vector<char>> level);
};

#endif