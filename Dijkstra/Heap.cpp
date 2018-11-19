//
// Created by Sangwon Lee on 10/14/18.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Heap.h"

heap::heap(int capacity) {
    this->capacity = capacity;
    this->data.resize(capacity + 1);
    this->mapping =  new hashTable(capacity * 2);
    this->filled = 0;

}

int heap::insert(const std::string &id, int key, void *pv) {
    if(filled == capacity) {
        return 1;
    }
    else if(mapping->contains(id)) {
        return 2;
    }
    else {
        //Start at index 1
        filled++;

        //Initialize new node
        node newNode;// = data[filled];
        newNode.id = id;
        newNode.key = key;
        newNode.pData = pv;
        mapping->insert(id,  &data[filled]);
        data[filled] = newNode;
        percolateUp(filled);
        return 0;
    }
}

void heap::percolateUp(int posCur) {
    node temp = data[posCur];
    while(posCur > 1 && temp.key < data[/*floor*/(posCur/2)].key ) {
        // move parent node to child node
        data[posCur] = data[floor(posCur/2)];
        // set pointer of moved (parent) node;
        mapping->setPointer(data[posCur].id, &data[posCur]);
        // set posCur to half its val
        posCur /= 2;
    }
    // place temp node in correct place
    data[posCur] = temp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getIndex(node * ptr) {
    return int(ptr - &data[0]);
}

int heap::setKey(const std::string &id, int newKey) {
    // Check to see if id exists already
    if(!mapping->contains(id)) {
        return 1;
    }

    node * ptr = (node *) mapping->getPointer(id);
    int oldKey = ptr->key;
    ptr->key = newKey;

    int pos = getIndex(ptr);
    mapping->setPointer(data[pos].id, &data[pos]);

    // Maintain heap order property!
    if(oldKey > ptr->key) {
        percolateUp(getIndex(ptr));
    }
    if(oldKey < ptr->key) {
        percolateDown(getIndex(ptr));
    }
    return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
    if(filled == 0) {
        return 1;
    }
    else {
        //Write to respective addresses if arguments are supplied
        if(pId != nullptr) {
            *pId = data[1].id;
        }
        if(pKey != nullptr) {
            *pKey = data[1].key;
        }
        if(ppData != nullptr) {
            *(static_cast<void **> (ppData)) = data[1].pData;
        }
        mapping->remove(data[1].id);
        data[1] = data[filled];
        filled--;
        percolateDown(1);
        return 0;
    }
}

void heap::percolateDown(int posCur) {
    int child;
    node temp = data[posCur];

    for(; posCur * 2 <= filled; posCur = child) {
        child = posCur * 2;
        if((child != filled) && (data[child + 1].key < data[child].key)) {
           child++;
        }
        if(data[child].key < temp.key) {
            // Swap current node with child node
            data[posCur] = data[child];
            // Set swap in hash table
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }
        else {
            break;
        }
    }
    data[posCur] = temp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}


int heap::remove(const std::string &id, int *pKey, void *ppData) {
    if(!mapping->contains(id)) {
        return 1;
    }

    node * ptr = (node *) mapping->getPointer(id);

    if(pKey != nullptr) {
        *pKey = ptr->key;
    }
    if(ppData != nullptr) {
        *(static_cast<void **> (ppData)) = ptr->pData;
    }
    setKey(id,-INT_MAX);
    deleteMin();
    return 0;
}
