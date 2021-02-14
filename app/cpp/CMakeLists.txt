cmake_minimum_required(VERSION 3.10)

project(rushhour)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if (UNIX)
    enable_testing()
    add_subdirectory(test)
endif (UNIX)