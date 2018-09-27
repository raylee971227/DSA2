//
// Created by Sangwon Lee on 9/24/18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>

#include "hash.h"

using namespace std;

//getPrime function
unsigned int hashTable::getPrime(int size){
    unsigned int prime[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                            393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,
                            25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    int i = 0;

    while(prime[i] < size){
        i++;
    }
    return prime[i];
}

//Constructor
hashTable::hashTable(int size){
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;
}

unsigned long hashTable::hash(const std::string &key){
    //djb2 Hash Algorithm
    unsigned long hash = 5831;
    const char *c = key.c_str();
    while (*c++){
        hash = ((hash << 5) + hash) + (int)*c;
    }
    return hash;
}


//find position function
int hashTable::findPos(const std::string &key){
    int pos = hash(key) % capacity;

    if (data[pos].key.compare(key) == 0)
        return pos;
    else
        //Linear Probe
        for (int i = 1; i < data.size(); i++)
            if (data[(i + pos)].isOccupied && data[(i + pos)].key.compare(key) == 0)
                return (i + pos);
            else if (!data[(i + pos)].isOccupied) //Breaks if there is a break HashTable
                break;
    return -1;
}

//contains function
bool hashTable::contains(const string &key) {
    return(findPos(key) != -1);
}

//insert key into hashtable
int hashTable::insert(const string &key, void *pv) {
    if(contains(key)) {
        return 1;
    }

    int pos = hash(key) % capacity;

    //Linear probe
    while(data[pos].isOccupied) {
        pos = (pos + 1) % capacity;
    }

    data[pos].key = key;
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].pv = pv;

    //rehash check
    if(filled / capacity  >= 0.5) {
        bool rehashCheck = rehash();
        if(!rehash()){
            return 2;
        }
    }
    return 0;
}

//rehash function
bool hashTable::rehash() {
    //old hashtable
    vector<hashItem> temp = data;
    int newCap = getPrime(capacity);
    data.clear(); //clear entries from hashtable

    data.resize(newCap);
    if(data.size() != newCap) {
        cout << "Rehash failed" << endl;
        return false;
    }

    filled = 0;

    //refill hash table
    for(int i = 0; i < temp.size(); i++) {
        insert(temp[i].key, temp[i].pv);
    }

    return true;
}