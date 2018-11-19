cmake_minimum_required(VERSION 3.10)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 11)

add_executable(Dijkstra main.cpp Heap.h Heap.cpp hash.h hash.cpp Graph.cpp Graph.h)