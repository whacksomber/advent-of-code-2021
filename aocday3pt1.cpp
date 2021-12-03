#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    //declare ifstream variable and open input file
    ifstream inFile;
    inFile.open("input.txt");

    //12 bits in each binary number

    string binaryNum;
    char currentBit;

    vector<string> nums;


    int num0; //represents the number of 0s in the current bit position
    int num1; //represents the number of 1s in the current bit position

    while (!inFile.eof()) {
        getline(inFile, binaryNum); //retrieve one line of file
        nums.push_back (binaryNum); //add binary number string to vector
    }

    string gammaStr;

    //gamma rate bits
    //loop through the vector

    for (int n=0; n <= nums[0].length(); n++) {
        num0 = 0;
        num1 = 0;
        for (int i=0; i < nums.size(); i++) {
            //get nth bit of current binary number in vector
            currentBit = nums[i][n];

            if (currentBit == '0') {num0 += 1;}
            if (currentBit == '1') {num1 += 1;}
        }
    
        //after looping through each binary number, compare number of 0s and 1s in current bit position
        if (num0 > num1) {gammaStr += '0';}
        if (num1 > num0) {gammaStr += '1';}
    }

    int gammaDec = 0;

    //convert gamma binary to decimal
    for (int a = 0; a <= gammaStr.length()-1 ; a++) {
        int bit = 0;
        if (gammaStr[a] == '0') {bit = 0;}
        if (gammaStr[a] == '1') {bit = 1;}

        int pos = (gammaStr.length()-1) - a;

        gammaDec += bit * pow(2,pos);
    }


    //find epsilon rate
    string epString;

    for (int n=0; n <= nums[0].length(); n++) {
        num0 = 0;
        num1 = 0;
        for (int i=0; i < nums.size(); i++) {
            //get nth bit of current binary number in vector
            currentBit = nums[i][n];

            if (currentBit == '0') {num0 += 1;}
            if (currentBit == '1') {num1 += 1;}
        }
    
        //after looping through each binary number, compare number of 0s and 1s in current bit position
        if (num0 < num1) {epString += '0';}
        if (num1 < num0) {epString += '1';}
    }

    int epDec = 0;

    //convert gamma binary to decimal
    for (int a = 0; a <= epString.length()-1 ; a++) {
        int bit = 0;
        if (epString[a] == '0') {bit = 0;}
        if (epString[a] == '1') {bit = 1;}

        int pos2 = (epString.length()-1) - a;

        epDec += bit * pow(2,pos2);
    }
    
    //calculate consumption rate
    int con = epDec * gammaDec;

    cout << con << endl;
}