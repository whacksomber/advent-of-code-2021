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

struct board {
    int boardArr[5][5];
    bool markedCells [5][5];

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
    void searchBoard (int q) { //search board for number q
        for (int x=0; x < 5; x++) {
            for (int y=0; y < 5; y++) { if (boardArr[x][y] == q) { markedCells[x][y] = true; } }
        }
    }
    bool won () { //check for victory
        bool win = false;

        for (int r = 0; r < 5 && !win; r++) { //check each row of board for a win
            if (markedCells[r][0] && markedCells[r][1] && markedCells[r][2] && markedCells[r][3] && markedCells[r][4]) {
                win = true; //if all cells in one row are marked, win is true
            }
        }

        for (int c = 0; c < 5 && !win; c++) { //check each column of board for a win
            if (markedCells[0][c] && markedCells[1][c] && markedCells[2][c] && markedCells[3][c] && markedCells[4][c]) {
                win = true; //if all cells in one column are marked, win is true
            }
        }

        if (win) {return true;}
        else {return false;}
    }
    int score (int justCalled) {
        int sumNotMarked = 0;

        for (int x=0; x < 5; x++) {
            for (int y=0; y < 5; y++) {
                if (markedCells[x][y] == false) {sumNotMarked += boardArr[x][y];}
            }
        }
        return (justCalled * sumNotMarked);
    }
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
    string line; //temp variable to store one row of a board in while loop

    vector<board>allBoards; //vector of boards
    
    while (!inFile.eof()) {
        board tempBoard; //declare tempBoard variable
        //store one board
        int row = 0; //set row count to 0 each time a new row is processed
        while (getline(inFile, line) && !line.empty()) { //parse one row
            tempBoard.setRow (row, line); //set row values
            //end of row
            row++; //increment row count
        }
        allBoards.push_back(tempBoard); //add to vector
    }

    bool v = false; //determines whether a victory has been reached
    board winningBoard;
    int s; //final score

    //read one number at a time, then search for it in the bingo cards
    for (int i = 0; i < calledNums.size() && !v; i++) {
        for (int a=0; a < allBoards.size(); a++) {
            allBoards[a].searchBoard(calledNums[i]);
            //everytime a search is conducted, check for wins.
            if (allBoards[a].won()) {
                winningBoard = allBoards[a];
                v = true; //set 'v' flag to true, signifying a victory and thus causing the loop to end
                s = winningBoard.score(calledNums[i]); //compute winning score
            }
        }
    }

    cout << "Winning Score: " << s << endl;
}