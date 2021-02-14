#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <memory>
#include <chrono>

#include "puzzle.h"
#include "state.h"
#include "node.h"

struct AStar
{
    Puzzle *puzzle;

    AStar(Puzzle *puzzle) :
        puzzle(puzzle)
    {
    }

    virtual ~AStar()
    {
    }

    std::deque<State> build_path(Node *current)
    {
        std::deque<State> path;
        Node *node = current;
        while (node) {
            // copy state
            path.push_front(node->state);
            node = node->parent;
        }

        return path;
    }

    int find_node(std::vector<Node *> &nodelist, Node *node) {
        auto &node_state = node->state;
        for (int i = 0; i < nodelist.size(); i++) {
            auto &nl_node = nodelist[i];
            auto &nl_node_state = nl_node->state;
            if (nl_node_state.var_pos == node_state.var_pos) {
                return i;
            }
        }

        return -1;
    }

    std::deque<State> solve()
    {
        auto &initial_node = puzzle->initial_node;
        std::vector<std::unique_ptr<Node>> nodes;
        // copy node
        nodes.push_back(std::make_unique<Node>(initial_node->state, initial_node->depth, initial_node->parent));
        // start with root node
        std::vector<Node*> open = {nodes[0].get()};
        std::vector<Node*> closed;

        while (!open.empty()) {
            std::sort(open.begin(), open.end(), [](auto &a, auto &b) {
                return a->depth < b->depth;
            });
            Node *current = open[0];
            open.erase(open.begin());
            if (current->state.is_goal()) {
                auto path = build_path(current);
                return path;
            }

            closed.push_back(current);
            for (auto &successor : closed[closed.size() - 1]->expand()) {
                nodes.push_back(std::move(successor));
                if (find_node(open, nodes[nodes.size() - 1].get()) != -1) {
                    update_open(open, nodes[nodes.size() - 1].get());
                }
                else if (find_node(closed, nodes[nodes.size() - 1].get()) == -1) {
                    open.push_back(nodes[nodes.size() - 1].get());
                }
            }
        }

        return {};
    }

    void update_open(std::vector<Node *> &open, Node *successor) {
        int existing_index = find_node(open, successor);
        auto &existing = open[existing_index];
        if (existing->depth > successor->depth) {
            Node *successor_new = successor;
            open.erase(open.begin() + existing_index);
            open.push_back(successor_new);
        }
    }
};

void read_board(std::string file, Puzzle *puzzle) {
    std::ifstream infile(file);
    std::string line;
    std::array<std::array<char, 6>, 6> grid;
    int i = 0;
    while (std::getline(infile, line)) {
        int j = 0;
        for (auto c : line) {
            grid[i][j] = c;
            j += 1;
        }
        i += 1;
    }
    infile.close();

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (grid[i][j] != '.') {
                puzzle->car_names.insert(grid[i][j]);
            }
        }
    }

    std::unordered_map<char, int> var_pos;

    for (auto car_name : puzzle->car_names) {

        std::vector<std::pair<int, int>> squares;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (grid[i][j] == car_name) {
                    squares.push_back({ i, j });
                }
            }
        }

        bool orientation = true;
        for (auto &square : squares) {
            if (square.second != squares[0].second) {
                orientation = false;
                break;
            }
        }

        auto size = squares.size();
        int fp = (orientation) ? squares[0].second : squares[0].first;
        int vp = (orientation) ? squares[0].first : squares[0].second;

        puzzle->car_orientation[car_name] = orientation;
        puzzle->car_size[car_name] = size;
        puzzle->fixed_position[car_name] = fp;
        var_pos[car_name] = vp;
    }

    State state(puzzle, var_pos);
    puzzle->initial_node = std::make_unique<Node>(state, 0, nullptr);
    puzzle->search_count = 1;
}

int main(int argc, char *argv[]) {

    auto total_t1 = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < 41; i++) {
        
        Puzzle puzzle;

        std::string dir = argv[1];
        std::string file = dir + "/jam_" + std::to_string(i) + ".txt";
        read_board(file, &puzzle);

        AStar solver(&puzzle);
        auto t1 = std::chrono::high_resolution_clock::now();
        solver.solve();
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        std::cout << "[" << i << "] " << "search count: " << solver.puzzle->search_count;
        std::cout << " (" << duration << " ms" << ")" << std::endl;
    }

    auto total_t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( total_t2 - total_t1 ).count();
    std::cout << "total: (" << duration << " ms" << ")" << std::endl;

    return 0;
}
