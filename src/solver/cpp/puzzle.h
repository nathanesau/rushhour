#pragma once

#include <unordered_set>
#include <unordered_map>
#include <memory>

// forward declarations
struct Node;

struct Puzzle
{
    std::unordered_set<char> car_names;

    std::unordered_map<char, bool> car_orientation;
    
    std::unordered_map<char, size_t> car_size;

    std::unordered_map<char, int> fixed_position;

    std::unique_ptr<Node> initial_node;

    int search_count = 1;

    Puzzle();

    virtual ~Puzzle();
};
