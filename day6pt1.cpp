#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int numDays = 80;

class fish {
    int days;
    bool isNew;

    public:
        void setDays(int x) { days = x; }
        fish (int x) { setDays(x); isNew = false; } //constructor
        fish () {setDays(8); isNew = true;} //default constructor
        int getDays() { return days; }
        bool newFish() { return isNew; }
        void setNew(bool n) { isNew = n; }
};

void updateFish (vector<fish>&vec) {
    for (int d = 0; d < numDays; d++) {
        //update number of fish after d days
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].getDays() == 0) {
                fish newFish; //temp variable
                vec.push_back(newFish); //add new fish
                vec[i] = 6; //reset # of days to 6
            }
            else if (!vec[i].newFish()){ vec[i].setDays(vec[i].getDays()-1); }
            if (vec[i].newFish()) {vec[i].setNew(false);} //make new fish not new
        }
    }
}

int main() {
    ifstream inFile ("day6input.txt"); //open input file

    string str;
    getline(inFile, str);

    stringstream ss (str);
    string temp;
    vector<fish>fishes; //vector of fish

    while (getline(ss, temp, ',')) {
        int d;
        stringstream ss2; ss2 << temp; ss2 >> d;
        fish tempFish (d);
        fishes.push_back(tempFish);
    }

    updateFish(fishes);
    cout << "answer: " << fishes.size() << '\n';
}