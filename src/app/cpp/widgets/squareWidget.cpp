#include "squareWidget.h"
#include "boardWidget.h"
#include "../utility/string.h"

SquareWidget::SquareWidget(int row, int col, BoardWidget *boardWidget, QWidget *parent) :
    row(row),
    col(col),
    boardWidget(boardWidget),
    QLabel(parent)
{
    setFont(QFont("Times", 36));
    setStyleSheet("border: 3px solid black;");
}

void SquareWidget::updateAlpha(int alpha)
{
    auto style = styleSheet();
    
    std::string background = "";
    std::vector<std::string> otherTokens;
    for (std::string token : utility::split(style.toStdString(), ";"))
    {
        if (token.find("background") != std::string::npos)
        {
            background = token;
        }
        else
        {
            otherTokens.push_back(token);
        }
    }

    std::string rgba = utility::split(background, ":")[1];
    utility::trim(rgba);

    int index = rgba.find("rgba");
    auto rgbaTokens = utility::split(rgba.substr(index+5, rgba.size() - (index+6)), ",");
    std::string newRgba =  "rgba(" + utility::trim(rgbaTokens[0]) + ", " + utility::trim(rgbaTokens[1]) + ", " 
        + utility::trim(rgbaTokens[2]) + ", " + std::to_string(alpha) + ")";
    
    std::string newBackground = "background: " + newRgba;
    
    std::string newStyle = "";
    for (std::string token : otherTokens)
    {
        newStyle += token + "; ";
    }
    newStyle += newBackground + ";";

    setStyleSheet(QString::fromStdString(newStyle));
}

void SquareWidget::mousePressEvent(QMouseEvent *event)
{
    if (text() != ".") {
        boardWidget->onSquareClicked(this);
    }
}