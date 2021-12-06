#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    //declare ifstream variable
    ifstream inFile;
    inFile.open("day1input.txt");


    //declare vector to store depths
    vector<int> depthNum;
    vector<int>sums;

    string depthStr;
    int depth;

    //loop through the file line by line and add each value to a vector
    while (!inFile.eof()) {
        getline(inFile, depthStr);

        stringstream ss;
        ss << depthStr;
        ss >> depth;

        depthNum.push_back (depth);
    }

    int currentSum = 0;

    //loop through vector
    for (int i = 0; i < (depthNum.size()-3); i++) {
        currentSum = depthNum[i] + depthNum[i+1] + depthNum[i+2];
        sums.push_back(currentSum);
    }

    int timesIncreased = 0;

    for (int i = 1; i < sums.size(); i++) {
        if (sums[i] > sums[i-1]) {timesIncreased += 1;}
    }

    cout << "Increased " << timesIncreased << " times!" << endl;
}