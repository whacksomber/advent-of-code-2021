#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//function to parse csv lines, specifically the one at the top with the numbers
void parseCSV (string str, vector<int>&vec) {
    stringstream csv (str);

    string tempStr; int temp; //temp variables

    while (getline(csv, tempStr, ',')) {
        stringstream ss; ss << tempStr; ss >> temp;
        vec.push_back(temp);
    }
}

class board {
    int boardArr[5][5];
    bool markedCells [5][5];
    int score;

    public:
    void setRow (int row, string rowString) { //parse row
        int col = 0; //set initial column index to 0
        int cell;
        stringstream lineRow (rowString);
        while (lineRow >> cell) {
            boardArr[row][col] = cell;
            col++;
        }
        for (int x=0; x < 5; x++) {
            for (int y=0; y < 5; y++) { markedCells[x][y] = false; }
        }
    }
    void searchBoard (int q) {
        //search board for number q
        for (int x=0; x < 5; x++) {
            for (int y=0; y < 5; y++) { if (boardArr[x][y] == q) { markedCells[x][y] = true; } }
        }
    }
    bool won () {
        //check for victory
        bool win = false;

        for (int i = 0; i < 5; i++) {
            if (markedCells[i][0] && markedCells[i][1] && markedCells[i][2] && markedCells[i][3] && markedCells[i][4]) {
                win = true;
            }
        }

        for (int i = 0; i < 5; i++) {
            if (markedCells[0][i] && markedCells[1][i] && markedCells[2][i] && markedCells[3][i] && markedCells[4][i]) {
                win = true;
            }
        }

        if (win) {return true;}
        else {return false;}
    }
    void setScore (int justCalled) {
        int sumNotMarked = 0;

        for (int x=0; x < 5; x++) {
            for (int y=0; y < 5; y++) {
                if (markedCells[x][y] == false) {sumNotMarked += boardArr[x][y];}
            }
        }
        score = justCalled * sumNotMarked;
    }
    int getScore () {return score;}
};

int main() {
    ifstream inFile ("day4input.txt"); //declare ifstream variable and open input file

    //first, store the called numbers at the top of the file
    string numStr; //string to store the csv of numbers at the top
    getline(inFile, numStr); //retrieve one line of file, store in binaryNum
    vector<int>calledNums; //declare vector to store called numbers
    parseCSV(numStr, calledNums); //call function to parse csv line

    string emptyLine; //string to skip a line
    getline (inFile, emptyLine);
    string line;

    vector<board>allBoards; //vector of boards
    
    while (!inFile.eof()) {
        board tempBoard; //declare tempBoard variable
        //store one board
        //line is the temp variable to store strings
        int row = 0;
        while (getline(inFile, line) && !line.empty()) { //parse one row
            tempBoard.setRow (row, line); //set row values
            //end of row
            row++; //increment row count
        }
        allBoards.push_back(tempBoard); //add to vector
    }

    vector<board>winningBoards; //vector to store winning boards

    //read one number at a time, then search for it in the bingo cards
    for (int i = 0; i < calledNums.size(); i++) {
        for (int a=0; a < allBoards.size(); a++) {
            bool skip = false; //declare bool skip variable to determine whether current board should be skipped
            if (allBoards[a].won()) { skip = true; } //check if board has already won, if so, skip

            //if board has not already won, check for called number
            if (!skip) {
                allBoards[a].searchBoard(calledNums[i]); //search for called number on board
                if (allBoards[a].won()) { //check if board has won
                    allBoards[a].setScore(calledNums[i]); //set score of winning board
                    winningBoards.push_back(allBoards[a]); //add winning board to vector
                }
            }
        }
    }
    board last = winningBoards[winningBoards.size()-1];

    cout << "ANSWER: " << last.getScore() << endl;
}