#include "car.h"

Car::Car(const std::vector<std::pair<int, int>> &squares, char name, std::string color) :
    squares(squares), name(name), color(color)
{
}

void Car::clear()
{
    squares.clear();
    name = '\0';
    color = "";
}