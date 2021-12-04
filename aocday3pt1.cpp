#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

//function to convert binary to decimal
int binaryToDec(string n) {
    int decimal = 0;

    //convert binary to decimal
    for (int a = 0; a <= n.length()-1 ; a++) {
        int bit = 0;
        if (n[a] == '0') {bit = 0;}
        if (n[a] == '1') {bit = 1;}

        int pos = (n.length()-1) - a;

        decimal += bit * pow(2,pos);
    }
    return decimal;
}

int main() {
    //declare ifstream variable and open input file
    ifstream inFile;
    inFile.open("day3input.txt");

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

    //convert gamma binary to decimal
    int gamma = binaryToDec(gammaStr);


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

    //convert epsilon binary to decimal
    int ep = binaryToDec(epString);
    
    //calculate consumption rate
    int con = ep * gamma;

    cout << con << endl;
}