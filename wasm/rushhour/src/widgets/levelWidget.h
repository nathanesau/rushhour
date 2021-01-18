#pragma once

#include "../common.h"

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
private:
    std::vector<std::vector<char>> level;
    std::vector<std::map<std::string, std::string>> cars;

    QPushButton *editBtn;
    QPushButton *applyBtn;
    QLabel *originalBoardLabel;
    QLabel *currentBoardLabel;
    QTextEdit *originalBoardTE;
    QTextEdit *currentBoardTE;
    QHBoxLayout *menuLayout;
    QVBoxLayout *mainLayout;

public:
    LevelWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // data
        level.clear();
        cars.clear();

        // widgets
        editBtn = new QPushButton("Edit");
        applyBtn = new QPushButton("Apply");
        originalBoardLabel = new QLabel("Original Board");
        currentBoardLabel = new QLabel("Current Board");
        originalBoardTE = new QTextEdit();
        originalBoardTE->setReadOnly(true);
        originalBoardTE->setStyleSheet("background: lightgrey");
        currentBoardTE = new QTextEdit();
        currentBoardTE->setReadOnly(true);

        // layouts
        menuLayout = new QHBoxLayout();
        menuWidget->addWidget(editBtn);
        menuWidget->addWidget(applyBtn);
        mainLayout = new QVBoxLayout();
        mainLayout->addWidget(originalBoardLabel);
        mainLayout->addLayout(menuLayout);
        mainLayout->addWidget(originalBoardTE);
        mainLayout->addWidget(currentBoardLabel);
        mainLayout->addWidget(currentBoardTE);

        setLayout(mainLayout);
    }

    QTextEdit *getOriginalBoardTE()
    {
        return originalBoardTE;
    }

    QTextEdit *getCurrentBoardTE()
    {
        return currentBoardTE;
    }

    void parseLevel(std::vector<std::vector<char>> pLevel)
    {
        level = pLevel;
        std::set<char> pCars;
        // pCars = set([c for row in self.level for c in row if c != '.'])
        // self.cars = dict((k, {"squares": [], "name": k, "color": "rgba(255, 0, 0, 255)" if k == 'X' else COLORS[i]}) for i, k in enumerate(cars))

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (cars.find(pLevel[i][j]) != pChars.end())
                {
                    auto car = pLevel[i][j];
                    // cars[car]["squares"].push_back(i, j);
                }
            }
        }
    }

    /**
     * @brief check whether the provided level is valid or not.
     * 
     * @param levelText level as a string which can be parsed to 2D array of char.
     * 
     * @return true if level valid, false otherwise.
     */
    bool validateLevel(std::string levelText)
    {
        //if len([line for line in levelText.splitlines() if line.strip()]) != 6:
        //# wrong num rows
        //return False
        
        //if any(len(list(line)) != 6 for line in levelText.splitlines() if line.strip()):
        //# wrong num cols
        //return False

        return true;
    }

    void setOriginalLevel(const std::vector<std::vector<char>> &level)
    {
        // data
        parseLevel(level);

        // original board
        //self.originalBoardTE.setPlainText('\n'.join([''.join(square) for square in level]))
        //cursor = self.originalBoardTE.textCursor()
        //cursor.movePosition(QTextCursor.End)
        //self.originalBoardTE.setTextCursor(cursor)

        // current board
        //self.currentBoardTE.setPlainText('\n'.join([''.join(square) for square in level]))
    }

    void setCurrentLevel(const std::vector<std::vector<char>> &level)
    {
        // data
        parseLevel(level);
        
        // current board
        //self.currentBoardTE.setPlainText('\n'.join([''.join(square) for square in level]))
    }
};