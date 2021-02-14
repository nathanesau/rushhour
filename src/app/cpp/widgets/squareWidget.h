#ifndef SQUAREWIDGET_H
#define SQUAREWIDGET_H


#include "../common.h"
// forward declarations
class BoardWidget;

class SquareWidget : public QLabel
{
    int row;
    int col;
    BoardWidget *boardWidget;

public:
    SquareWidget(int row, int col, BoardWidget *boardWidget, QWidget *parent = nullptr);
    
    int getRow()
    {
        return row;
    }

    int getCol()
    {
        return col;
    }

    void updateAlpha(int alpha);

    void mousePressEvent(QMouseEvent *event) override;
};

#endif