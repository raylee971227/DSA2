cmake_minimum_required(VERSION 3.10)
project(spell)

set(CMAKE_CXX_STANDARD 11)

add_executable(spell main.cpp HashTable.h HashTable.cpp)