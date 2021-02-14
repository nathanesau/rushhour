use clap::App;
use clap::Arg;

use std::collections::HashMap;
use std::collections::VecDeque;

use lazy_static::lazy_static;
use std::sync::Mutex;

lazy_static! {
    // static variable related to person(s)
    pub static ref SEARCH_COUNT: Mutex<usize> = Mutex::new(0);
}

pub fn search_count_get() -> usize {
    *SEARCH_COUNT.lock().unwrap()
}

pub fn search_count_set(val: usize) {
    let x: &mut usize = &mut *SEARCH_COUNT.lock().unwrap();
    *x = val;
}

pub struct Puzzle {
    pub car_names: Vec<char>,
    pub car_orientation: HashMap<char, bool>,
    pub car_size: HashMap<char, usize>,
    pub fixed_position: HashMap<char, usize>
}

impl Puzzle {
    pub fn new() -> Puzzle {
        Puzzle {
            car_names: vec![],
            car_orientation: HashMap::new(),
            car_size: HashMap::new(),
            fixed_position: HashMap::new()
        }
    }
}

pub struct State<'a> {
    pub puzzle: &'a Puzzle,

    pub variable_position: HashMap<char, usize>,
}

impl<'a> State<'a> {
    pub fn is_goal(&self) -> bool {
        return self.variable_position[&'x'] == 5;
    }

    pub fn get_grid(&self) -> [[char; 6]; 6] {

        let mut grid: [[char; 6]; 6] = [['.'; 6]; 6];

        for car_name in self.puzzle.car_names.iter() {
            let orientation = self.puzzle.car_orientation[car_name];
            let mut size = self.puzzle.car_size[car_name];
            let fp = self.puzzle.fixed_position[car_name];
            if *car_name == 'x' && (self.variable_position[car_name] + size) > 6 {
                size -= 1;
            }
            if orientation { // vertical
                for d in 0..size {
                    grid[self.variable_position[car_name] + d][fp] = *car_name;
                }
            }
            else { // horizontal
                for d in 0..size {
                    grid[fp][self.variable_position[car_name] + d] = *car_name;
                }
            }
        }
        
        return grid;
    }

    pub fn expand(&self) -> Vec<State<'a>> {
        
        let grid = self.get_grid();
        let mut new_states: Vec<State<'a>> = vec![];

        for car_name in self.puzzle.car_names.iter() {
            let p = self.variable_position[car_name];
            let fp = self.puzzle.fixed_position[car_name];
            let orientation = self.puzzle.car_orientation[car_name];

            for np in (0..p).rev() {
                if orientation && grid[np][fp] != '.' { // vert
                    break;
                }
                if !orientation && grid[fp][np] != '.' { // hor
                    break;
                }
                let mut new_variable_position = self.variable_position.clone();
                new_variable_position.insert(*car_name, np);
                new_states.push(State {
                    puzzle: self.puzzle,
                    variable_position: new_variable_position
                });
            }

            let car_size = self.puzzle.car_size[car_name];
            for np in p+car_size..=6 {
                if np < 6 && orientation && grid[np][fp] != '.' {
                    break;
                }
                if np < 6 && !orientation && grid[fp][np] != '.' {
                    break;
                }
                if np == 6 && *car_name != 'x' {
                    break;
                }
                let mut new_variable_position = self.variable_position.clone();
                new_variable_position.insert(*car_name, np - car_size + 1);
                new_states.push(State {
                    puzzle: self.puzzle,
                    variable_position: new_variable_position
                });
            }
        }

        let sc = search_count_get();
        search_count_set(sc + new_states.len());

        return new_states;
    }
}

pub struct Node<'a> {
    pub idx: usize,
    pub state: State<'a>,
    pub depth: usize,
    pub parent_idx: usize,
}

impl<'a> Node<'a> {
    pub fn expand(&self, idx: usize) -> Vec<Node<'a>> {

        let new_states = self.state.expand();
        let mut new_nodes: Vec<Node> = vec![];
        let mut new_node_idx = idx;
        for state in new_states {
            new_nodes.push(Node {
                idx: new_node_idx,
                state: state,  // NOTE: move state
                depth: self.depth + 1,
                parent_idx: self.idx,
            });
            new_node_idx += 1;
        }

        return new_nodes;
    }
}

fn parse_board(s: &String) -> (Puzzle, HashMap<char, usize>) {

    let mut puzzle = Puzzle::new();

    let mut grid: [[char; 6]; 6] = [['.'; 6]; 6];

    let lines = s.split('\n').map(String::from).collect::<Vec<String>>();
    for (i, line) in lines.iter().enumerate() {
        if i >= 6 {
            break;
        }
        let chars: Vec<char> = line.chars().collect();
        for (j, c) in chars.iter().enumerate() {
            if j >= 6 {
                break;
            }
            grid[i][j] = *c;
        }
    }

    for i in 0..6 {
        for j in 0..6 {
            if grid[i][j] != '.' && !puzzle.car_names.contains(&grid[i][j]) {
                puzzle.car_names.push(grid[i][j]);
            }
        }
    }

    let mut variable_position = HashMap::new();
    for car_name in &puzzle.car_names {
        let mut squares: Vec<(usize, usize)> = vec![];
        for i in 0..6 {
            for j in 0..6 {
                if grid[i][j] == *car_name {
                    squares.push((i, j));
                }
            }
        }

        let mut orientation = true;
        for s in &squares[1..] {
            if s.1 != squares[0].1 {
                orientation = false;
                break;
            }
        }

        let fp = if orientation {
            squares[0].1
        } else {
            squares[0].0
        };
        let vp = if orientation {
            squares[0].0
        } else {
            squares[0].1
        };

        puzzle.car_orientation.insert(*car_name, orientation);
        puzzle.car_size.insert(*car_name, squares.len());
        puzzle.fixed_position.insert(*car_name, fp);
        variable_position.insert(*car_name, vp);
    }

    return (puzzle, variable_position);
}

pub fn astar_build_path<'a>(_: &Node) -> VecDeque<State<'a>> {
    let path: VecDeque<State> = VecDeque::new();
    // todo
    return path;
}

pub fn astar_find_node<'a>(nodes: &Vec<Node>, node_idx_list: &Vec<usize>, node_idx: &usize) -> bool {

    let node: &Node = &nodes[*node_idx];

    let node_state = &node.state;
    for i in 0..node_idx_list.len() {
        let nl_node_index = &node_idx_list[i];
        let nl_node = &nodes[*nl_node_index];
        let nl_node_state = &nl_node.state;
        if nl_node_state.variable_position == node_state.variable_position {
            return true;
        }
    }

    return false;
}

pub fn astar_update_open<'a>(nodes: &Vec<Node>, open: &mut Vec<usize>, node_idx: &usize) {

    let node: &Node = &nodes[*node_idx];

    let mut index = 0;
    let node_state = &node.state;
    for i in 0..open.len() {
        let nl_node_index = &open[i];
        let nl_node = &nodes[*nl_node_index];
        let nl_node_state = &nl_node.state;
        if nl_node_state.variable_position == node_state.variable_position {
            index = i;
            break;
        }
    }

    let existing_index = &open[index];
    let existing = &nodes[*existing_index];
    if existing.depth > node.depth {
        open.remove(index);
        open.push(node.idx);
    }
    
}

// NOTE: initial_node is moved into the function
pub fn astar_solve<'a>(initial_node: Node<'a>) -> Option<VecDeque<State<'a>>> {

    // keep all nodes in a vector
    let mut nodes: Vec<Node<'a>> = vec![];

    let root_idx = initial_node.idx;

    // NOTE: initial_node is copied into root node
    let root: Node<'a> = Node {
        idx: root_idx,
        state: State {
            puzzle: initial_node.state.puzzle,
            variable_position: initial_node.state.variable_position
        },
        depth: initial_node.depth,
        parent_idx: initial_node.parent_idx
    };

    nodes.push(root);

    // start with root node
    let mut open: Vec<usize> = vec![root_idx];
    let mut closed: Vec<usize> = vec![];
    
    while !open.is_empty() {
        open.sort_by(|a, b| {
            if nodes[*a].depth < nodes[*b].depth {
                return std::cmp::Ordering::Less;
            } else if nodes[*a].depth == nodes[*b].depth {
                return std::cmp::Ordering::Equal;
            } else {
                return std::cmp::Ordering::Greater;
            }
        });

        // clone here because we erase the shared ptr from open afterwards
        let current_idx = open[0];

        // remove from open
        open.remove(0);

        if nodes[current_idx].state.is_goal() {
            let path = astar_build_path(&nodes[current_idx]);
            return Some(path);
        }

        // add to closed
        closed.push(current_idx);

        // get new nodes (idx starting from nodes.len())
        let new_nodes = nodes[current_idx].expand(nodes.len());

        for successor in new_nodes {

            let node_idx = successor.idx;

            let node: Node<'a> = Node {
                idx: node_idx,
                state: State {
                    puzzle: successor.state.puzzle,
                    variable_position: successor.state.variable_position
                },
                depth: successor.depth,
                parent_idx: successor.parent_idx
            };

            // keep all nodes in a vector
            nodes.push(node);

            if astar_find_node(&nodes, &open, &node_idx) {
                astar_update_open(&nodes, &mut open, &node_idx);
            }
            else if !astar_find_node(&nodes, &closed, &node_idx) {
                open.push(node_idx);
            }
        }
    }

    return Option::None;
}

pub fn main() {
    let clap_app = App::new("rushhour_solver").arg(
        Arg::with_name("jamdir")
            .long("jamdir")
            .takes_value(true)
            .default_value("jams")
            .help("specify the directory containg jam files"),
    );

    let matches = clap_app.get_matches();
    let jamdir = matches.value_of("jamdir").unwrap();

    for i in 1..=40 {

        let board = std::fs::read_to_string(format!("{}/jam_{}.txt", jamdir, i))
        .expect("jam file was not found in provided jamdir!");

        let info = parse_board(&board);
        let puzzle = info.0;
        let variable_position = info.1;

        // NOTE: parent_idx not used for root
        let initial_node = Node {
            idx: 0,
            state: State {
                puzzle: &puzzle,
                variable_position: variable_position
            },
            depth: 0,
            parent_idx: 0,
        };

        search_count_set(1);
        let _ = astar_solve(initial_node);

        println!("[{}] search_count: {}", i, search_count_get());
    }
}
