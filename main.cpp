#include <iostream>

using namespace std;

typedef struct piece {
    int player; // 1 for player one, 2 for player two
    int position = -1;
    char c;
} piece_struct;

typedef struct innerBoard {
    // used to store where the inner board is located
    int current_position; // position
    int valid_locations[9] = {6,7,8,11,12,13,16,17,18};
} innerBoard_struct;

typedef struct OuterBoard {
    // holds inner_board, and all piece positions
    innerBoard * inner = new innerBoard;
    piece * pieces = (piece*) malloc(sizeof(piece)*8);
} OuterBoard_struct;


void printHeader(char* progName) {
    cout << progName << endl
            << "Author: Wynn Drahorad" << endl
            << "Lab: Tues 9am" << endl
            << "System:  Windows 10, Qt IDE" << endl;

    return;
}

int convertInputToIndex(OuterBoard * outer, int input) {
    // converts user inputted number to board index
    return outer->inner->valid_locations[input-1];
}

void setValidLocations(OuterBoard * outer, int validLocations[9][9], int gridLocation) {
    for (int i = 0; i < 9; i++) {
        outer->inner->valid_locations[i] = validLocations[gridLocation-1][i];
    }

    return;
}

void initPieces(OuterBoard* board) {
    piece * thePieces = board->pieces;

    for (int i = 0; i < 4; ++i) {
        thePieces[i].c = 'A'+i;
        thePieces[i].player = 1;

        thePieces[i+4].c = 'a'+i;
        thePieces[i+4].player = 2;
    }

    return;
}

void printLocation(OuterBoard * outer, int locToCheck) {
    printf(" ");
    for (int i = 0; i < 9; ++i) {
        if (outer->pieces[i].position == locToCheck) {
            printf("%c", outer->pieces[i].c);
        }
    }

    printf(" ");
}

void printBoard(OuterBoard * outer) {

    printf("-------------------\n");
    for (int row = 1; row < 6; ++row) {

    }

}

int main()
{
    bool win = false;
    char progName[] = "Program 5: Tic Tac Two";
    int validLocations[9][9] = {{1,2,3,6,7,8,11,12,13},
                                {2,3,4,7,8,9,12,13,14},
                                {5,6,7,10,11,12,15,16,17},
                                {6,7,8,11,12,13,16,17,18},
                                {7,8,9,12,13,14,17,18,19},
                                {10,11,12,15,16,17,20,21,22},
                                {11,12,13,16,17,18,21,22,23},
                                {12,13,14,17,18,19,22,23,24},
                                {13,14,15,18,19,20,23,24,25}};


    // begin run program
    printHeader(progName);

    while(!win) {

    }


    return 0;
}

