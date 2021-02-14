cmake_minimum_required(VERSION 3.10)

project(solver)

add_executable(solver
    main.cpp
    node.cpp
    node.h
    puzzle.cpp
    puzzle.h
    state.cpp
    state.h
)
