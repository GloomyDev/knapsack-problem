cmake_minimum_required(VERSION 3.18)

project(KnapsackProblem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Backtracking back.cpp)
add_executable(BruteForce brute.cpp)
add_executable(DynamicProgramming dynamic.cpp)
add_executable(KnapsackGenerator generator.cpp)
