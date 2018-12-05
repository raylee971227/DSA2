/*
 *  Raymond Lee
 *  ECE-365: DSA II
 *  Merge Program
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int matrix[1001][1001];

void checkMerge(string inputFile, string outputFile) {
    string str1, str2, str3;

    ifstream instream(inputFile.c_str());
    if (!instream) {
        cerr << "Error: Could not successfully open input file " << inputFile << endl;
        return;
    }

    ofstream outstream(outputFile.c_str());
    if (!outstream) {
        cerr << "Error: Could not successfully open outpu file" << outputFile << endl;
        return;
    }

    while (instream >> str1 >> str2 >> str3) {
        if (str1.length() + str2.length() != str3.length()) {
            outstream << "*** NOT A MERGE ***" << endl;
        }
        else {
            // initialize 2-D matrix to 0
            memset(matrix, 0, sizeof(matrix));
            matrix[0][0] = 1; // starting point

            for (int j = 0; j <= str2.length(); j++) {
                for (int i = 0; i <= str1.length(); i++) {
                    if (matrix[i][j]) {
                        // check against "merged" string && look ahead
                        if (str1[i] == str3[i + j] && !matrix[i + 1][j]) {
                            matrix[i + 1][j] = 2;
                        }
                        if (str2[j] == str3[i + j] && !matrix[i][j + 1]) {
                            matrix[i][j + 1] = 3;
                        }
                    }
                }
            }

            int i = str1.length();
            int j = str2.length();

            if (matrix[i][j] != 0) {
                while (i > 0 && j >= 0) {
                    int k = i + j - 1;

                    if (matrix[i][j] == 2) {
                        str3[k] = toupper(str3[k]);
                        i--;
                    }
                    else{
                        j--;
                    }
                }
                outstream << str3 << endl;
            }
            else {
                outstream << "*** NOT A MERGE ***" << endl;
            }
        }
    }
}

int main() {
    string inputFileName, outputFileName;

    cout << "Enter name of input file:  ";
    cin >> inputFileName;

    cout << "Enter name of output file: ";
    cin >> outputFileName;

    checkMerge(inputFileName, outputFileName);

    return 0;
}