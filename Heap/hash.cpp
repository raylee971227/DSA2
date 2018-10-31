//
// Created by Sangwon Lee on 10/15/18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "hash.h"

using namespace std;

//getPrime function
unsigned int hashTable::getPrime(int size){
    int size2 = size * 2;
    unsigned int prime[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                            393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,
                            25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    int i = 0;

    while(prime[i] <= size2){
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

    if (data[pos].key.compare(key) == 0 && !data[pos].isDeleted) {
        return pos;
    }
    else{
        //Linear Probe
        for (int i = 1; i < data.size(); i++)
            if (data[(i + pos)].isOccupied && data[(i + pos)].key.compare(key) == 0)
                return (i + pos);
            else if (!data[(i + pos)].isOccupied) //Breaks if there is a break HashTable
                break;
    }
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
    filled++;

    //rehash check
    if(double(filled) / double(capacity)  >= 0.5) {
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

    //set isOccupied to false
    for(int i = 0; i < data.size(); i++) {
        data[i].isOccupied = false;
    }

    data.resize(newCap);
    capacity = newCap;
    //error check
    if(data.size() != newCap) {
        cout << "Rehash failed" << endl;
        return false;
    }

    filled = 0;

    //refill hash table
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i].isOccupied) {
            insert(temp[i].key, temp[i].pv);
        }
    }

    return true;
}

bool hashTable::remove(const string &key) {
    int pos = findPos(key);
    if(pos != -1) {
        data[pos].isOccupied = false;
        data[pos].isDeleted = true;
        filled--;
        return true;
    }
    else {
        return false;
    }
}

void* hashTable::getPointer(const std::string &key, bool *b) {
    int pos = findPos(key);
    if(pos >= 0) {
        if(b != nullptr) {
            *b = true;
        }
        return data[pos].pv;
    }
    else {
        if(b != nullptr) {
            *b = false;
        }
        return nullptr;
    }
}


int hashTable::setPointer(const std::string &key, void *pv) {
    int pos = findPos(key);
    if(pos != -1) {
        data[pos].pv = pv;
        return 0;
    }
    else {
        return 1;
    }
}