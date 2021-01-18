#ifndef CAR_H
#define CAR_H

#include "common.h"

struct Car
{
    std::vector<std::pair<int, int>> squares;
    char name;
    std::string color;

    Car() = default;

    Car(const std::vector<std::pair<int, int>> &squares, char name, std::string color);

    void clear();
};

#endif