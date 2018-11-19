//
// Created by Sangwon Lee on 11/15/18.
//

#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#include <list>
#include <string>
#include <vector>

#include "hash.h"

using namespace std;

class Graph {

private:
    class Vertex;

    class Edge {
    public:
        int cost;
        Vertex * next;
    };

    class Vertex {
    public:
//        void insertEdge(Vertex * next, int cost);
        string name = "";
        bool visited = false;
        int distance = INT_MAX;
        Vertex * previous = nullptr;
        list<Edge> adjacency;
    };

    hashTable * graphTable;
    list<Vertex *> nodeList;


public:
    Graph();

    void readFile(const string &file);
    void dijkstra(string &startVertexName);
    bool contains(string &vertex);
    void report(string &vertexName, string &outfile);

};

#endif //DIJKSTRA_GRAPH_H
