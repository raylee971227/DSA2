//
// Created by Sangwon Lee on 11/14/18.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <fstream>
#include <string>

#include "hash.h"
#include "Heap.h"
#include "Graph.h"

using namespace std;

int main() {
    string infileName, outfileName, v1 , v1_cpy;

    Graph* graph = new Graph();

    cout << "Enter name of graph file: ";
    cin >> infileName;

    graph->readFile(infileName);

    cout << "Enter a valid vertex id for the starting vertex: ";
    cin >> v1;

    v1_cpy = v1;

    if(!(graph->contains(v1))) {
        cerr << "ERROR: Vertex \"" << v1 << "\" does not exist!" << endl;
        exit(-1);
    }

    clock_t start = clock();

    graph->dijkstra(v1);

    clock_t end = clock();

    double elapsedTime = (double)(end-start) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to apply Dijkstra's Algorithm: " << elapsedTime << endl;

    cout << "Enter name of output file: ";
    cin >> outfileName;

    graph->report(v1_cpy, outfileName);

    return 0;
}