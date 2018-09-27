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

//hashTable::hashTable(int size){
//    //Constructor
//    capacity = getPrime(size*2);
//    data.resize(capacity);
//    filled = 0;
//}
//
//int hashTable::insert(const std::string &key, void *pv){
//    if(contains(key)){
//        //No need to enter values more than once
//        return 1;
//    }
//    int pos = hash(key) % capacity;
//
//    // Collision Detection (Linear Probing)
//    while(data[pos].isOccupied){
//        pos = (pos + 1) % capacity;
//        //Divide By Capacity to avoid going outside bounds
//    }
//
//    // New HashItem Entry
//    data[pos].pv = pv;
//    data[pos].isOccupied = true;
//    data[pos].isDeleted = false;
//    data[pos].key = key;
//    filled++;
//
//    // Size Check in case of Rehashing
//    if(capacity / 2 < filled){
//        bool tmp = rehash();
//        if(tmp == false){
//            return 2;
//        }
//    }
//
//    return 0;
//}
//
//bool hashTable::contains(const std::string &key){
//    //Checks if findPos returns a value corresponding to a key
//    if(findPos(key) != -1){
//        return true;
//    } else{
//        return false;
//    }
//}
//
//void *hashTable::getPointer(const std::string &key, bool *b){
//    int pos = findPos(key);
//    if(pos != -1){
//        if(b != nullptr){
//            *b = true;
//        }
//        return data[pos].pv;
//    }
//    else{
//        if(b != nullptr){
//            *b = false;
//        }
//        return nullptr;
//    }
//}
//
//int hashTable::setPointer(const std::string &key, void *pv){
//    int pos = findPos(key);
//    if(pos != -1){
//        data[pos].pv = pv;
//        return 0;
//    }
//    else{
//        return 1;
//    }
//}
//
//bool hashTable::remove(const std::string &key){
//    int pos = findPos(key);
//    if(pos != -1){
//        data[pos].isDeleted = true;
//        return true;
//    }
//    return false;
//}
//
//unsigned long hashTable::hash(const std::string &key){
//    //Referred to djb2 Hash Algorithm
//    int hash = 5831;
//    const char *c = key.c_str();
//
//    while (*c++){
//        hash = ((hash << 5) + hash) + (int)*c;
//    }
//    return hash;
//}
//
//int hashTable::findPos(const std::string &key){
//    //pos used to start at current index
//    int pos = hash(key) % capacity;
//
//    while(pos < capacity && data[pos].isOccupied && data[pos].key.compare(key)){
//        pos++;
//    }
//    if(pos < capacity && data[pos].isOccupied && !data[pos].key.compare(key) && !data[pos].isDeleted){
//        return pos;
//    }
//
//    //pos loops back to beginning due to linear probing
//    if(pos == capacity){
//        pos = 0;
//    }
//    while(pos < capacity && data[pos].isOccupied && data[pos].key.compare(key)){
//        pos++;
//    }
//    if(data[pos].isOccupied && !data[pos].key.compare(key) && !data[pos].isDeleted){
//        return pos;
//    }
//
//    return -1;
//
//}
//
//bool hashTable::rehash(){
//    vector<hashItem> tmp = data;
//    int oldCapacity = capacity;
//    //Reset HashTable
//    for(int i = 0; i < capacity; i++){
//        data[i].isOccupied = false;
//        data[i].isDeleted = true;
//    }
//
//    capacity = getPrime(capacity * 2);
//    data.resize(capacity);
//    if(data.size() != capacity){
//        return false;
//    }
//    //Empty HashTable
//    filled = 0;
//    //Reinsert Data Values
//    for(int i = 0; i < oldCapacity; i++){
//        if(!tmp[i].isDeleted && tmp[i].isOccupied){
//            insert(tmp[i].key, tmp[i].pv);
//        }
//    }
//    //Clear Vector to avoid memory leaks
//    vector<hashItem>().swap(tmp);
//    return true;
//
//}

unsigned int hashTable::getPrime(int size){
    unsigned int prime[] = {1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189,805306457, 1610612741, 3221225533};
    int num = 0;
    /*
    Error Checking Since Rehash Can't Return a Number twice 3221225533 (Max unsigned int = 4294967295)
    if(size > 3221225533){
      cout << "Size of Inputs is too Large for unsigned int" << endl;
      return -1;
    }
    */
    while(prime[num] < size){
        num++;
    }
    return prime[num];
}

#include "hash.h"

using namespace std;


//getPrime function
unsigned int getPrime(int size){
    unsigned int prime[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                            393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,
                            25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    int i = 0;
    while(prime[i] < size) {
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