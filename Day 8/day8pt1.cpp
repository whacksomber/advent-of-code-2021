#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main () {
    ifstream inFile ("day8input.txt"); //open input file

    string wholeLine;

    int ans = 0;

    while (getline(inFile, wholeLine)) {
        size_t pos = 0;
        string s; //string to store one side of delimiter

        size_t found2 = wholeLine.find(" | ") + 3;
        string part2 = wholeLine.substr (found2);
        stringstream ss (part2);

        string temp;

        while (getline(ss, temp, ' ')) {
            //test if each temp string passed has 2, 3, 4, or 7 characters
            int l = temp.length();
            //cout << temp << " -> " << l << endl;
            if (l == 2 || l == 3 || l == 4 || l == 7) { ans++; }
        }
    }

    cout << "answer: " << ans << endl;
}