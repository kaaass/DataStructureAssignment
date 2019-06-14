cmake_minimum_required(VERSION 3.14)
project(data_strcut_assign)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)

add_executable(assignment1 assignment1/expr.cpp)

add_subdirectory(assignment2)

add_subdirectory(assignment3)

add_subdirectory(assignment4)

add_subdirectory(huffman)