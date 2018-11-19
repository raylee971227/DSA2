//
// Created by Sangwon Lee on 11/14/18.
//

#include "hash.h"

using namespace std;

hashTable::hashTable(int size){
  //Constructor
  capacity = getPrime(size*2);
  data.resize(capacity);
  filled = 0;
}

int hashTable::insert(const std::string &key, void *pv){
  if(contains(key)){
    //No need to enter values more than once
    return 1;
  }
  int pos = hash(key) % capacity;

  // Collision Detection (Linear Probing)
  while(data[pos].isOccupied && !data[pos].isDeleted){
    pos = (pos + 1) % capacity;
    //Divide By Capacity to avoid going outside bounds
  }

  // New HashItem Entry
  data[pos].pv = pv;
  data[pos].isOccupied = true;
  data[pos].isDeleted = false;
  data[pos].key = key;
  filled++;

  // Size Check in case of Rehashing
  if(capacity / 2 < filled){
    bool tmp = rehash();
    if(tmp == false){
      return 2;
    }
  }

  return 0;
}

bool hashTable::contains(const std::string &key){
  //Checks if findPos returns a value corresponding to a key
  if(findPos(key) != -1){
    return true;
  } else{
    return false;
  }
}

// Not Necessary for this Assignment
void *hashTable::getPointer(const std::string &key, bool *b){
  int pos = findPos(key);
  if(pos != -1){
      if(b != nullptr){
          *b = true;
      }
    return data[pos].pv;
  }
  else{
    if(b != nullptr){
      *b = false;
    }
    return nullptr;
  }
}

// Not Necessary for this Assignment
int hashTable::setPointer(const std::string &key, void *pv){
  // Since Key is provided just use findPos
  int pos = findPos(key);
  if(pos != -1){
    data[pos].pv = pv;
    return 0;
  }
  else{
    return 1;
  }
}

bool hashTable::remove(const std::string &key){
  int pos = findPos(key);
  if(pos != -1){
    data[pos].isDeleted = true;
    return true;
  }
  return false;
}

unsigned long hashTable::hash(const std::string &key){
  //Referred to djb2 Hash Algorithm
  unsigned long hash = 5831;
  const char *c = key.c_str();

  while (*c++){
    hash = ((hash << 5) + hash) + (int)*c;
  }
  return hash;
}

int hashTable::findPos(const std::string &key){
  //pos used to start at current index
  int pos = hash(key) % capacity;
  // Checks to see if entry is occupied and to see if keys are different
  while(pos < capacity && data[pos].isOccupied && data[pos].key.compare(key)){
    pos++;
  }
  if(pos < capacity && data[pos].isOccupied && !data[pos].key.compare(key) && !data[pos].isDeleted){
    return pos;
  }

  //pos loops back to beginning due to linear probing
  if(pos == capacity){
    pos = 0;
  }
  while(pos < capacity && data[pos].isOccupied && data[pos].key.compare(key)){
    pos++;
  }
	if(data[pos].isOccupied && !data[pos].key.compare(key) && !data[pos].isDeleted){
    return pos;
  }

  return -1;

}

bool hashTable::rehash(){
  vector<hashItem> tmp = data;
  int oldCapacity = capacity;
  //Reset HashTable
  for(int i = 0; i < capacity; i++){
    data[i].isOccupied = false;
    data[i].isDeleted = true;
  }

  //Expand Size of HashTable
  capacity = getPrime(capacity * 2);
  data.resize(capacity);
  if(data.size() != capacity){
    return false;
  }
  //Empty HashTable
  filled = 0;
  //Reinsert Data Values
  for(int i = 0; i < oldCapacity; i++){
    if(!tmp[i].isDeleted && tmp[i].isOccupied){
      insert(tmp[i].key, tmp[i].pv);
    }
  }
  //Clear Vector to avoid memory leaks
  vector<hashItem>().swap(tmp);
  return true;

}

unsigned int hashTable::getPrime(int size){
    // Precomputed Array
    unsigned int prime[] = {1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
       393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
       100663319, 201326611, 402653189, 805306457, 1610612741, 3221225533};
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