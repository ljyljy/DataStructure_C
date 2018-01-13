cmake_minimum_required(VERSION 3.8)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        DivideConquer
        Tree
        AggregationSearch
        Graph/UnionFindSet.cpp Graph/Dijkstra.h Graph/FLoyd_Dijkstra.cpp Graph/Prim.cpp)
add_executable(DataStructure ${SOURCE_FILES} Graph/UnionFindSet.cpp)