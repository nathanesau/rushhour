#include "levelWidget.h"
#include "../utility/string.h"

LevelWidget::LevelWidget(QWidget *parent) : QWidget(parent)
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
    currentBoardTE->setStyleSheet("background: lightgrey");

    // layouts
    menuLayout = new QHBoxLayout();
    menuLayout->addWidget(editBtn);
    menuLayout->addWidget(applyBtn);
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(originalBoardLabel);
    mainLayout->addLayout(menuLayout);
    mainLayout->addWidget(originalBoardTE);
    mainLayout->addWidget(currentBoardLabel);
    mainLayout->addWidget(currentBoardTE);

    setLayout(mainLayout);
}

 void LevelWidget::parseLevel(std::vector<std::vector<char>> pLevel)
{
    level.clear();
    cars.clear();

    level = pLevel;
    std::set<char> pCars;
    for (auto &row : pLevel)
    {
        for (auto c : row)
        {
            if (c != '.')
            {
                pCars.insert(c);
            }
        }
    }

    int index = 0;
    for (auto pCar : pCars)
    {
        std::vector<std::pair<int, int>> squares;
        char name = pCar;
        std::string color = (pCar == 'X') ? "rgba(255, 0, 0, 255)" : COLORS[index];
        cars[pCar] = Car(squares, name, color);
        index += 1;
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (pCars.find(pLevel[i][j]) != pCars.end())
            {
                char pCar = pLevel[i][j];
                cars[pCar].squares.push_back({i, j});
            }
        }
    }
}

bool LevelWidget::validateLevel(std::string levelText)
{
    auto lines = utility::split(levelText, "\n");

    if (lines.size() != 6)
    {
        // wrong num rows
        return false;
    }

    for (auto line : lines)
    {
        std::vector<char> v(line.begin(), line.end());
        if (v.size() != 6) 
        {
            // wrong num cols
            return false;
        }
    }
    
    return true;
}

void LevelWidget::setOriginalLevel(std::vector<std::vector<char>> level)
{
    // data
    parseLevel(level);

    std::string levelText = "";
    for (int i = 0; i < 6; i++)
    {
        std::string s(level[i].begin(), level[i].end());
        levelText += s;
        levelText += "\n";
    }

    // original board
    originalBoardTE->setPlainText(QString::fromStdString(levelText));
    auto cursor = originalBoardTE->textCursor();
    cursor.movePosition(QTextCursor::End);
    originalBoardTE->setTextCursor(cursor);

    // current board
    currentBoardTE->setPlainText(QString::fromStdString(levelText));
}

void LevelWidget::setCurrentLevel(std::vector<std::vector<char>> level)
{
    // data
    parseLevel(level);

    std::string levelText = "";
    for (int i = 0; i < 6; i++)
    {
        std::string s(level[i].begin(), level[i].end());
        levelText += s;
        levelText += "\n";
    }

    // current board
    currentBoardTE->setPlainText(QString::fromStdString(levelText));
}