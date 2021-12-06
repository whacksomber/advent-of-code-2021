#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    //declare ifstream variable
    ifstream inFile;
    inFile.open("day2input.txt");

    //declare position variables
    int depth = 0, horizontal = 0, aim = 0;

    string position;
    string changeStr;
    int change;

    //loop through the file line by line
    while (inFile >> position >> changeStr) {
        stringstream ss; ss << changeStr; ss >> change;

        if (position=="forward") {
            horizontal += change;
            depth += (aim * change);
        }

        if (position=="down") {aim += change;}
        if (position=="up") {aim -= change;}
    }

    //multiply depth and horizontal position
    int result = depth * horizontal;

    cout << "The result is " << result << "!" << endl;
}