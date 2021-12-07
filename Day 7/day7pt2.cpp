#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int findMax(vector<int>v) {
    //find max position
    int max;
    for (int i=0; i < v.size(); i++) {
        if (i == 0) {max = v[i];}
        else {
            if (v[i] > max) {max = v[i];} //update max if new max has been found
        }
    }
    return max;
}

int main() {
    ifstream inFile ("day7input.txt"); //open input file

    string str; //temp string
    vector<int>pos; //vector to store all crab positions

    while (getline(inFile, str, ',')) {
        int temp;
        stringstream ss; ss << str; ss >> temp;
        pos.push_back(temp);
    }

    int max = findMax(pos); //find max position

    int minFuel;

    for (int i=0; i < max; i++) {
        int fuel = 0;
        for (int a=0; a < pos.size(); a++) {
            int steps = abs(i - pos[a]);
            for (int s=1; s<=steps; s++) { fuel += s; }
        }
        if (i==0) {minFuel = fuel;}
        else { if (fuel < minFuel) { minFuel = fuel; } }
    }
    cout << "answer: " << minFuel << endl;
}