#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>

#include "HashTable.h"

using namespace std;

void lowerCase(string &key) {
    for(int i = 0; i < key.size(); i++) {
        key[i] = tolower(key[i]);
    }
}

bool isValidChar(int charInt) {
    return (isalpha(charInt) || isdigit(charInt) || charInt == 45 || charInt == 39);
}

int firstValidCharPosition(string &line, int initialInd) {
    for(int i = initialInd; i <line.size(); i++) {
        if(isValidChar(line[i])) {
            return i;
        }
    }
    return -1;
}

void readThenWrite(string &line, ofstream &writeStream, hashTable *dictionary) {
    static int lineNum = 0; //Line number counter
    lineNum++;
    lowerCase(line);
    int start;
    string word;

    start = firstValidCharPosition(line, 0); //Finds first valid character in the string
    bool hasNum = isdigit(line[start]); //Checks if character is a number
    for (int i = start; i <= line.size(); i++) {
        if (start == -1) //If no start is found, skips line. All characters are invalid
            break;
        hasNum = hasNum || isdigit(line[i]);
        if (!isValidChar(line[i])) { //If character is found, parses word starting at that line
            word = line.substr(start, i - start);

            if (word.size() > 20)
                writeStream << "Long word at line " << lineNum << ", starts: " << word.substr(0, 20) << endl;
            else if (!hasNum && !dictionary->contains(word))
                writeStream << "Unknown word at line " << lineNum << ": " << word << endl;

            i = start = firstValidCharPosition(line, i); //Continues parsing line at the next valid character
            hasNum = isdigit(line[start]); //Checks if first character is a number
        }
    }

}

int main() {
    string dictFName, outputFName, inputFName;
    string input, line;
    hashTable *dict = new hashTable(50000);

    cout << "Enter name of dictionary: ";
    cin >> dictFName;

    ifstream dictStream(dictFName.c_str());
    if(!dictStream) {
        cout <<"Error: Dictionary " << dictFName << " not found." << endl;
        exit(-1);
    }

    clock_t startDict = clock();

    dictStream >> input;

    while(!dictStream.eof()) {
        lowerCase(input);
        dict -> insert(input);
        dictStream >> input;
    }
    clock_t endDict = clock();

    double dictTime = (double(endDict - startDict)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to load dictionary: " << dictTime << endl;
    dictStream.close();

    //GET INPUT FILE
    cout << "Enter name of input file: ";
    cin >> inputFName;

    ifstream inStream(inputFName.c_str());
    if(!inStream) {
        cout << "Error: Input file " << inputFName << " not found.";
        exit(-1);
    }

    //GET OUTPUT FILE
    cout << "Enter name of output file: ";
    cin >> outputFName;

    ofstream outStream;
    outStream.open(outputFName); //Open if exists, create new if not

    //SPELL CHECK
    clock_t startCheck = clock();
    do {
        getline(inStream, line);
        //check if word exits -->  output word to appropriate stream
        readThenWrite(line, outStream, dict);
    }
    while(!inStream.eof());



    clock_t endCheck = clock();

    double checkTime = double(endCheck - startCheck) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to check document: " << checkTime << endl;
    inStream.close(); //Closes input and output streams
    outStream.close();

    return 0;
}
