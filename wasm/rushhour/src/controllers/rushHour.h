#pragma once

#include "../common.h"

struct RushHour
{
    static const int UP = 0;
    static const int DOWN = 1;
    static const int LEFT = 2;
    static const int RIGHT = 3;

    static const int HORIZONTAL = 0;
    static const int VERTICAL = 1;

    const std::vector<std::vector<char>> &board;

    RushHour(const std::vector<std::vector<char>> &board) : board(board)
    {
    }

    /**
     * @brief moves car with given name for length steps in the step direction
     * 
     * @param carName 'x', 'a', etc.
     * @param dir UP, DOWN, LEFT or RIGHT
     * @param length number of steps to move
     * 
     * @return true if move is valid, false otherwise
     */
    bool makeMove(char carName, int dir, int length)
    {
        std::vector<std::pair<int, int>> squares;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (board[i][j] == carName)
                {
                    squares.push_back(std::make_pair(i, j));
                }
            }
        }

        int rotation = VERTICAL;
        for(auto square : squares) {
            if(square.second != squares[0].second) {
                rotation = HORIZONTAL;
                break;
            }
        }

        // check if dir conflicts with rotation
        if ((rotation == HORIZONTAL && (dir != LEFT && dir != RIGHT)) ||
            (rotation == VERTICAL && (dir != UP && dir != DOWN))
        {
            return false;
        }

        // check for edge of board and collisions
        for (int i = 1; i <= length; i++) {
            auto edge = (dir == LEFT || dir == RIGHT) ? squares[0] : squares[squares.size() - 1];
            auto new_edge = (dir == LEFT) ? std::make_pair(edge.first, edge.second - i) :
                (dir == RIGHT) ? std::make_pair(edge.first, edge.second + i) :
                (dir == UP) ? std::make_pair(edge.first - i, edge.second) :
                (dir == DOWN) ? std::make_pair(edge.first + i, edge.second) :
                std::make_pair(0, 0);
            
            // check if boundary check satisfied
            if (new_edge.first < 0 || new_edge.first >= 6 || new_edge.second < 0 || new_edge.second >= 6) {
                return false;
            }

            // check for collision
            if (board[new_edge.first][new_edge.second] != '.') {
                return false;
            }
        }

        // get the new squares after the move
        std::vector<std::pair<int, int>> new_squares;
        for (auto square : squares) {
            auto new_square = (dir == LEFT) ? std::make_pair(square.first, square.second - i) :
                (dir == RIGHT) ? std::make_pair(square.first, square.second + i) :
                (dir == UP) ? std::make_pair(square.first - i, square.second) :
                (dir == DOWN) ? std::make_pair(square.first + i, square.second) :
                std::make_pair(0, 0);
            new_squares.push_back(new_square);
        }

        // perform the move
        for (auto square : squares) {
            board[square.first][square.second] = '.';
        }

        for (auto square : new_squares) {
            board[square.first][square.second] = carName;
        }

        return true;
    }

    /**
     * @return true if and only if board solved (i.e. XX car touching right edge)
     * @return false otherwise
     */
    bool isSolved()
    {
        char carName = 'x';

        std::vector<std::pair<int, int>> squares;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (board[i][j] == carName)
                {
                    squares.push_back(std::make_pair(i, j));
                }
            }
        }

        auto edge = squares[1];

        return edge.second == 5;
    }
};