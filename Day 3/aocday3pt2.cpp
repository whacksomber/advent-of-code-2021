#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

//function to convert from binary to decimal
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

int narrowDown (vector<string>vec, int bitNum, char rating) {
    if (bitNum == 0 || vec.size() == 1) { return binaryToDec(vec[0]); } //base case

    int bitLength = vec[0].length(); //get the number of bits to search

    bool keep0 = false, keep1 = false;
    int num0 = 0, num1 = 0;
    int n = bitLength - bitNum; //get the current index to search

    vector<string>filteredVec; //values that match the criteria are stored here

    for (int i = 0; i < vec.size(); i++) { //loop through vector and get nth bit of each item
        char countBit = vec[i][n];

        if (countBit == '0') {num0 += 1;}
        if (countBit == '1') {num1 += 1;}
    }

    //set bool variables depending on rating type
    if (num0 > num1) { //more 0s than 1s
        if (rating == 'o') {keep0 = true;}
        if (rating == 'c') {keep1 = true;}
    }
    if (num1 > num0) { //more 1s than 0s
        if (rating == 'o') {keep1 = true;}
        if (rating == 'c') {keep0 = true;}
    }
    if (num1 == num0) { // 1 == 0
        if (rating == 'o') {keep1 = true;}
        if (rating == 'c') {keep0 = true;}
    }

    if (keep1 && !keep0) {
        for (int i = 0; i < vec.size(); i++) {
            char bit = vec[i][n];
            if (bit == '1') { filteredVec.push_back(vec[i]); }
        }
    }

    if (keep0 && !keep1) {
        for (int i = 0; i < vec.size(); i++) {
            char bit = vec[i][n];
            if (bit == '0') { filteredVec.push_back(vec[i]); }
        }
    }

    return narrowDown(filteredVec, bitNum-1, rating);
}

int main() {
    ifstream inFile ("day3input.txt"); //declare ifstream variable and open input file
    vector<string> nums; //vector to store binary values from input file

    while (!inFile.eof()) { //read each line of input file into vector
        string binaryNum; //temporary variable to store line from file
        getline(inFile, binaryNum); //retrieve one line of file, store in binaryNum

        nums.push_back (binaryNum);
    }

    int oxygenDec = narrowDown (nums, nums[0].length(), 'o'); //find oxygen generator rating
    int co2Dec = narrowDown (nums, nums[0].length(), 'c'); //find co2 scrubber rating

    cout << "Solution: " << co2Dec * oxygenDec << endl;
}
