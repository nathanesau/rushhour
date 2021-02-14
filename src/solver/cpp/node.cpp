#include "node.h"
#include "state.h"

#include <utility>
#include <memory>

Node::Node(State state, int depth, Node *parent) : 
    state(state), depth(depth), parent(parent)
{    
}

Node::~Node()
{
}

std::vector<std::unique_ptr<Node>> Node::expand()
{
    // copy state
    auto new_states = state.expand();
    std::vector<std::unique_ptr<Node>> new_nodes;
    for (auto &state : new_states) {
        new_nodes.push_back(std::make_unique<Node>(state, depth + 1, this));
    }

    return new_nodes;
}
