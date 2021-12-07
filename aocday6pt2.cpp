#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int numDays = 256;

int main() {
    ifstream inFile ("day6input.txt"); //open input file

    int64_t fishTypes[9] = {0};

    string temp;
    
    while (getline(inFile, temp, ',')) {
        int64_t d;
        stringstream ss; ss << temp; ss >> d;
        fishTypes[d]++;
    }

    for (int d = 0; d < numDays; d++) {
        //loop through array
        int64_t new0 = 0;

        for (int a=1; a<9; a++) {
            if (a == 1) {new0 += fishTypes[a];}
            fishTypes[a-1] += fishTypes[a];
            fishTypes[a] = 0;
        }
        //how about the ones that went from one to zero on this day
        fishTypes[6] = fishTypes[6] + (fishTypes[0]-new0);
        fishTypes[8] += fishTypes[8] + (fishTypes[0]-new0);
        fishTypes[0] = new0;
    }

    int64_t total = 0;
    for (int i=0; i < 9; i++) { total += fishTypes[i]; }

    cout << "answer: " << total << endl;
}