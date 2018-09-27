#include <iostream>
#include <array>
#include "HashTable.h"

using namespace std;

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    char hello[] = {'h','e','l','l','o'};
//    for(int i = 0; i < sizeof(hello); i++) {
//        std::cout << hello[i] << std::endl;
//    }
    Hash table(7);
//
    table.insertItem(1);
    table.insertItem(2);
    table.insertItem(3);
    table.insertItem(4);
    table.insertItem(5);
    table.displayHash();
    cout << "erase" << endl;
    table.deleteItem(3);
    table.displayHash();

    return 0;
}