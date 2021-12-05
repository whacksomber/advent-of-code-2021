#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int gridSize = 1000;
int grid[1000][1000] = {0};

class point {
    int x, y;

    public:
        point(int xValue, int yValue) {x = xValue; y = yValue;} //constructor
        point() {x = 0; y = 0;} //default constructor
        int getX () {return x;}
        int getY () {return y;}
        void set (int a, int b) { x = a; y = b; }
};

class vent {
    void makeLine();
    point startPoint, endPoint;

    public:
        vector<point>pointsCovered;
        void setFirstPoint (int x, int y) { startPoint.set(x,y); }
        void setEndPoint (int x, int y) { endPoint.set(x,y); }
        int x1 () {return startPoint.getX();}
        int x2 () {return endPoint.getX();}
        int y1 () {return startPoint.getY();}
        int y2 () {return endPoint.getY();}
        vent(int x_1, int y_1, int x_2, int y_2);
        point getStartPoint () {return startPoint;}
        point getEndPoint () {return endPoint;}
};

//gather all the points that a vent covers
void vent::makeLine() {
    int x1 = this->x1();
    int x2 = this->x2();
    int y1 = this->y1();
    int y2 = this->y2();

    if (x1 == x2) {
        int greaterY = max(y1, y2); int lessY = min(y1, y2);

        for (int y = lessY; y <= greaterY; y++) {
            point temp (x1, y);
            pointsCovered.push_back(temp);
        }
    }
    if (y1 == y2) {
        int greaterX = max(x1, x2); int lessX = min(x1, x2);

        for (int x = lessX; x <= greaterX; x++) {
            point temp (x, y1);
            pointsCovered.push_back(temp);
        }
    }
}

vent::vent(int x_1, int y_1, int x_2, int y_2) {
    setFirstPoint (x_1, y_1);
    setEndPoint (x_2, y_2);
    makeLine();
}

vent parseLine (string line) {
    size_t found = line.find(" -> ");
    string point1 = line.substr(0,found);

    stringstream ptstr1 (point1);
    string tempStr; int x_1, y_1;

    int count = 0;
    while (getline(ptstr1, tempStr, ',')) {
        stringstream ss; ss << tempStr;

        if (count == 0) {ss >> x_1;}
        if (count == 1) {ss >> y_1;}
        count++;
    }

    size_t posNext = line.find(" -> ") + 4;
    string point2 = line.substr (posNext);
    stringstream ptstr2 (point2);

    int x_2, y_2;

    count = 0;
    while (getline(ptstr2, tempStr, ',')) {
        stringstream ss; ss << tempStr;

        if (count == 0) {ss >> x_2;}
        if (count == 1) {ss >> y_2;}
        count++;
    }

    vent obj (x_1, y_1, x_2, y_2);
    return obj;
}

void makeGrid(vector<vent>v) {
    for (int i=0; i<v.size(); i++) { //go through array of vents
        for (int a=0; a<v[i].pointsCovered.size(); a++) { //go through points covered of each vent
            int x = v[i].pointsCovered[a].getX();
            int y = v[i].pointsCovered[a].getY();
            grid[x][y]++;
        }
    }
}

int main() {
    ifstream inFile ("day5input.txt");
    string lineFromFile;
    vector<vent>vents;

    while (getline(inFile, lineFromFile)) {
        vent temp = parseLine(lineFromFile);
        if (temp.x1() == temp.x2() || temp.y1() == temp.y2()) {vents.push_back(temp);}
    }

    makeGrid(vents);

    int numOverlap = 0;
    for (int x=0; x<gridSize; x++) {
        for (int y=0; y<gridSize; y++) {
            if (grid[x][y] >= 2) {numOverlap++;}
        }
    }

    cout << "result: " << numOverlap << endl;
}