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

    int timesIncreased = 0;

    for (int i = 1; i < depthNum.size(); i++) {
        if (depthNum[i] > depthNum[i-1]) {timesIncreased += 1;}
    }

    cout << "Increased " << timesIncreased << " times!" << endl;
}