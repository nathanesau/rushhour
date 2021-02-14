#pragma once

#include <array>
#include <unordered_map>
#include <vector>

// forward declarations
struct Puzzle;

struct State
{
    Puzzle *puzzle;
    
    std::unordered_map<char, int> var_pos;

    State(Puzzle *puzzle, std::unordered_map<char, int> var_pos);

    virtual ~State();

    bool is_goal() const;

    std::array<std::array<char, 6>, 6> get_grid();

    std::vector<State> expand();
};
