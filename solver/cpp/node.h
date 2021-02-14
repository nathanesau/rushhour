#pragma once

#include <memory>
#include <vector>

#include "state.h"

struct Node
{
    State state;

    int depth;

    Node *parent;

    // copy state
    Node(State state, int depth, Node *parent);

    virtual ~Node();

    std::vector<std::unique_ptr<Node>> expand();
};
