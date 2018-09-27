//
// Created by Sangwon Lee on 9/10/18.
//
#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <iostream>
#include <list>

using namespace std;

class Hash {
    int BUCKET;
    list<int>* table;

public:
    Hash(int bucketSize);
    int hashFunction(int value);
    void insertItem(int value);
    void deleteItem(int key);
    void displayHash();

};

Hash::Hash(int bucketSize) {
    this -> BUCKET = bucketSize;
    table = new list<int>[bucketSize];
}

int Hash::hashFunction(int value) {
    int modul = (BUCKET % value);
    return modul;
}

void Hash::insertItem(int value) {
    int index = hashFunction(value);
    table[index].push_back(value);
}

void Hash::deleteItem(int key) {
    list<int>::iterator i;
    int index = hashFunction(key);

    for(i = table[index].begin(); i != table[index].end(); i++) {
        if(*i == key) {
            table[index].erase(i);
            break;
        }
    }
}

void Hash::displayHash() {
    for(int i = 0; i < BUCKET; i++) {
        cout << i;
        for(auto j : table[i]) {
            cout << " -->" << j;
        }
        cout << endl;
    }
}

#endif //HASHTABLE_HASHTABLE_H
