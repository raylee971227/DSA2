//
// Created by Raymond Lee on 10/14/18.
//

#ifndef HEAP_HEAP_H

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <climits>
#include "hash.h"


using namespace std;

class heap {
public:
    //
    // heap - The constructor allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified capacity
    //
    heap(int capacity);

    //
    // insert - Inserts a new node into the binary heap
    //
    // Inserts a node with the specified id string, key,
    // and optionally a pointer. They key is used to
    // determine the final position of the new node.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is already filled to capacity
    //   2 if a node with the given id already exists (but the heap
    //     is not filled to capacity)
    //
    int insert(const std::string &id, int key, void *pv = NULL);

    //
    // setKey - set the key of the specified node to the specified value
    //
    // I have decided that the class should provide this member function
    // instead of two separate increaseKey and decreaseKey functions.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int setKey(const std::string &id, int key);

    //
    // deleteMin - return the data associated with the smallest key
    //             and delete that node from the binary heap
    //
    // If pId is supplied (i.e., it is not NULL), write to that address
    // the id of the node being deleted. If pKey is supplied, write to
    // that address the key of the node being deleted. If ppData is
    // supplied, write to that address the associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is empty
    //
    int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

    //
    // remove - delete the node with the specified id from the binary heap
    //
    // If pKey is supplied, write to that address the key of the node
    // being deleted. If ppData is supplied, write to that address the
    // associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

private:

    // node class
    class node {
    public:
        string id; //The id of this node
        int key; // The key of this node
        void *pData; //A pointer to the actual data
    };

    vector<node> data; //actual binary heap
    hashTable *mapping; //maps ids to node pointers
    int filled;
    int capacity;

    // Get the index in array from a node's pointer
    int getIndex(node * ptr);

    void percolateUp(int posCur);
    void percolateDown(int posCur);
};

#define HEAP_HEAP_H

#endif //HEAP_HEAP_H
