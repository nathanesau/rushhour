#include "state.h"
#include "puzzle.h"

State::State(Puzzle *puzzle, std::unordered_map<char, int> var_pos) :
    puzzle(puzzle), var_pos(var_pos)
{
}

State::~State()
{
}

bool State::is_goal() const
{
    auto it = var_pos.find('x');
    return it->second == 5;
}

std::array<std::array<char, 6>, 6> State::get_grid()
{
    std::array<std::array<char, 6>, 6> grid;
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            grid[i][j] = '.';
        }
    }

    for (auto car_name : puzzle->car_names) {
        auto orientation = puzzle->car_orientation[car_name];
        auto size = puzzle->car_size[car_name];
        auto fp = puzzle->fixed_position[car_name];
        if (car_name == 'x' && (var_pos[car_name] + size) > 6) {
            size -= 1;   
        }
        if (orientation) { // vertical
            for (int d = 0; d < size; d++) {
                grid[var_pos[car_name] + d][fp] = car_name;
            }
        }
        else { // horizontal
            for (int d = 0; d < size; d++) {
                grid[fp][var_pos[car_name] + d] = car_name;
            }
        }
    }

    return grid;
}

std::vector<State> State::expand()
{
    const std::array<std::array<char, 6>, 6> grid = get_grid();
    std::vector<State> new_states;

    for (auto car_name : puzzle->car_names) {
        auto p = var_pos[car_name];
        auto fp = puzzle->fixed_position[car_name];
        auto orientation = puzzle->car_orientation[car_name];

        for (int np = p - 1; np >= 0; np -= 1) {
            if (orientation && grid[np][fp] != '.') { // vert
                break;
            }
            if (!orientation && grid[fp][np] != '.') { // hor 
                break;
            }
            auto new_var_pos = var_pos;
            new_var_pos[car_name] = np;
            new_states.push_back(State(puzzle, new_var_pos));
        }

        int car_size = puzzle->car_size[car_name];
        for (int np = p+car_size; np <= 6; np++) {
            if (np < 6 && (orientation && grid[np][fp] != '.')) {
                break;
            }
            if (np < 6 && (!orientation && grid[fp][np] != '.')) {
                break;
            }
            if (np == 6 && car_name != 'x') {
                break;
            }
            auto new_var_pos = var_pos;
            new_var_pos[car_name] = np - car_size + 1;
            new_states.push_back(State(puzzle, new_var_pos));
        }
    }

    // for stats purpose
    puzzle->search_count += new_states.size();

    // copy state
    return new_states;
}
