#pragma once

#include "../common.h"

class SquareWidget : public QLabel
{
private:
    int row;
    int col;

public:
    SquareWidget(int row, int col, QWidget *parent = nullptr)
    {
    }

    void updateAlpha(int alpha)
    {
        auto style = styleSheet();
        // background = [e for e in style.split(';') if 'background' in e][0]
        // rgba = background.split(':')[1].strip()
        // r, g, b, a = rgba.replace('rgba', '').replace('(', '').replace(')', '').split(', ')
        // style = style.replace(background, background.replace(rgba, f'rgba({r}, {g}, {b}, {alpha})'))
        setStyleSheet(sheet);
    }

    void mousePressEvent(QEvent *event)
    {
        if (text() != ".") {
            parent().onSquareClicked(this);
        }
    }
}