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

string narrowDown (vector<string>vec, int bitNum, char rating) {
    if (bitNum == 0 || vec.size() == 1) { return vec[0]; } //base case

    //get the number of bits to search
    int bitLength = vec[0].length();

    bool keep0 = false, keep1 = false;

    int num0 = 0;
    int num1 = 0;

    vector<string>filteredVec;

    //search the current bit.

    //get the current index to search
    int n = bitLength - bitNum;

    //loop through vector and get nth bit of each item
    for (int i = 0; i < vec.size(); i++) {
        char countBit = vec[i][n];

        if (countBit == '0') {num0 += 1;}
        if (countBit == '1') {num1 += 1;}
    }

    //set bool variables
    if (num0 > num1) { //more 0s than 1s
        if (rating == 'o') {keep0 = true;}
        if (rating == 'c') {keep1 = true;}
        //depending on rating type, determine whether to keep
    }
    if (num1 > num0) { //more 1s than 0s
        //depending on rating type, determine whether to keep
        if (rating == 'o') {keep1 = true;}
        if (rating == 'c') {keep0 = true;}
    }
    if (num1 == num0) { // 1 == 0
        if (rating == 'o') {keep1 = true;}
        if (rating == 'c') {keep0 = true;}
    }

    if (keep1 == true && keep0 == false) {
        for (int i = 0; i < vec.size(); i++) {
            char bit = vec[i][n];
            if (bit == '1') { filteredVec.push_back(vec[i]); }
        }
    }

    else if (keep0 == true && keep1 == false) {
        for (int i = 0; i < vec.size(); i++) {
            char bit = vec[i][n];
            if (bit == '0') { filteredVec.push_back(vec[i]); }
        }
    }
    //remove vector elements that don't match the criteria

    return narrowDown(filteredVec, bitNum-1, rating);
}

int main() {
    ifstream inFile ("day3input.txt"); //declare ifstream variable and open input file

    //vectors to store binary values from input file
    vector<string> oxygenNums;
    vector<string> nums;
    vector<string>co2Nums;

    //read each line of input file into vector
    while (!inFile.eof()) {
        string binaryNum;

        getline(inFile, binaryNum); //retrieve one line of file

        nums.push_back (binaryNum);
        //oxygenNums.push_back(binaryNum);
        co2Nums.push_back(binaryNum);
    }

    int bitLength = nums[0].length();

    //find oxygen generator rating
    string oxygenBin = narrowDown (nums, bitLength, 'o'); //narrow down vector
    int oxygenDec = binaryToDec(oxygenBin); //convert to decimal

    //find co2 scrubber rating
    string co2Bin = narrowDown (nums, bitLength, 'c'); //narrow down vector
    int co2Dec = binaryToDec(co2Bin); //convert to decimal

    int ls = co2Dec * oxygenDec;

    cout << ls << endl;
}
