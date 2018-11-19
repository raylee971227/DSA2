//
// Created by Sangwon Lee on 11/15/18.
//

#include <stdio.h>
#include <fstream>
#include <istream>
#include <stack>

#include "Graph.h"
#include "Heap.h"
#include "hash.h"

using namespace std;

Graph::Graph() {
    graphTable = new hashTable(0);
}

bool Graph::contains(string &vertex) {
    return graphTable->contains(vertex);
}

void Graph::readFile(const string &file) {
    ifstream infile;
    infile.open(file.c_str());
    if(!infile) {
        cerr << "Error: unable to open file " << file << endl;
        exit(-1);
    }

    string vStart, vEnd;
    int dist;

    while(!infile.eof()) {
        infile >> vStart >> vEnd >> dist;


        Vertex *p_vStart;
        Vertex *p_vEnd;
        if (!graphTable->contains(vStart)) {
            p_vStart = new Vertex;
            p_vStart->name = vStart;
            nodeList.push_back(p_vStart);
            graphTable->insert(vStart, p_vStart);
        } else {
            p_vStart = (Vertex *) (graphTable->getPointer(vStart));
        }

        if (!graphTable->contains(vEnd)) {
            p_vEnd = new Vertex;
            p_vEnd->name = vEnd;
            nodeList.push_back(p_vEnd);
            graphTable->insert(vEnd, p_vEnd);
        } else {
            p_vEnd = (Vertex *) (graphTable->getPointer(vEnd));
        }

        Edge newEdge;
        newEdge.cost = dist;
        newEdge.next = p_vEnd;
        p_vStart->adjacency.push_back(newEdge);
    }
}



void Graph::dijkstra(string &startVertexName) {
    if (nodeList.empty()) {
        cerr << "Error: list of vertices is empty!" << endl;
        return;
    }

    // Get starting vertex
    Vertex *p_startVertex = (Vertex *) (graphTable->getPointer(startVertexName));
    p_startVertex->distance = 0;
    p_startVertex->previous = p_startVertex;

    // Heap to hold all vertices
    heap *dheap = new heap(nodeList.size());

    if((dheap->insert(startVertexName, p_startVertex->distance, p_startVertex)) != 0) {
        cerr << "Error inserting " << startVertexName << " into heap!" << endl;
        return;
    }


    for (list<Vertex *>::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter) {
        if ((*iter)->name != startVertexName) {
            dheap->insert((*iter)->name, (*iter)->distance, *iter);
        }
    }

    int currDist;
    Vertex *nextVertex;

    while (dheap->deleteMin(&startVertexName, &currDist, &nextVertex) == 0) {
        nextVertex = (Vertex *) (graphTable->getPointer(startVertexName));
        nextVertex->visited = true;

        if (nextVertex->previous == nullptr) {
            continue;
        }

        for (list<Edge>::iterator iter = nextVertex->adjacency.begin(); iter != nextVertex->adjacency.end(); ++iter) {
            if (!iter->next->visited) {
                int newDist = currDist + iter->cost;
                if (newDist >= iter->next->distance) {
                    continue;
                }

                iter->next->distance = newDist;
                dheap->setKey(iter->next->name, iter->next->distance);
                iter->next->previous = nextVertex;
            }
        }
    }
}

void Graph::report(string &vertexName, string &outfile) {

    Vertex *v = (Vertex *)(graphTable->getPointer(vertexName));

    ofstream output(outfile.c_str());
    if(!output) {
        cerr << "ERROR: could not read output file " << outfile << endl;
    }

    for(list<Vertex *>::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter) {
        Vertex * currentV = *iter;
        output << (*iter)->name << ": ";
        if((*iter)->previous == nullptr) {
            output << "NO PATH" << endl;
        }
        else {
            output << (*iter)->distance;

            // Stack variable to hold path to said vertex
            stack<string> path;
            if((*iter) != v) {
                path.push((*iter)->name);
            }

            // trace back from end
            Vertex * tracer = (*iter)->previous;
            while(tracer != v) {
                path.push(tracer->name);
                tracer = tracer->previous;
            }

            output << " [" << v->name;
            while(!path.empty()) {
                output << ", " << path.top();
                path.pop();
            }

            output << "]" << endl;
        }
    }
    output.close();
}
