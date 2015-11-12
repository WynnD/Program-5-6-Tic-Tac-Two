#include <iostream>

using namespace std;

typedef struct piece {
    int player; // 1 for player one, 2 for player two
    int position = -1; // stores position of piece
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

int getPieceIndex(OuterBoard * outer, char c) {
    for (int i = 0; i < 9; ++i) {
        if (outer->pieces[i].c == c) {
            return i;
        }
    }
    printf("Piece not found.\n");
    return -1;
}


void printHeader(char* progName) {
    cout << progName << endl
            << "Author: Wynn Drahorad" << endl
            << "Lab: Tues 9am" << endl
            << "System:  Windows 10, Qt IDE" << endl;

    return;
}

int convertInputToIndex(OuterBoard * outer, int input) {
    // converts user inner board index (1-9) to outer board index (1-25)
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

void printLocation(OuterBoard * outer, int outerLoc) {
    bool isPiece = false;
    printf(" ");
    for (int i = 0; i < 9; ++i) {
        if (outer->pieces[i].position == outerLoc) {
            printf("%c", outer->pieces[i].c);
            isPiece = true;
            break;
        }
    }

    if (!isPiece) {
        printf(".");
    }

    printf(" ");
}


bool isValidLoc(OuterBoard * outer, int location) {

    for (int i = 0; i < 9; ++i) {
        if (outer->pieces[i].position == convertInputToIndex(outer, location)) {
            printf("There is already a piece there. Please try again.");
            return false;
        }
    }

    return true;
}

bool charIsMoveable(OuterBoard * outer, char piece) {


    for (int i = 0; i < 9; ++i) {
        if (outer->inner->valid_locations[i] ==
                outer->pieces[getPieceIndex(outer, piece)].position)
            return true;
    }

    return false;
}

bool makeMove(OuterBoard * outer, int player, char c, int innerLocation) {

    if (c.tolower() == "m") {
        if (innerLocation > 0 && innerLocation < 10) {
            moveBoard(innerLocation);
        }
    } else {
        int piece = getPieceIndex(outer, c);
        if (piece == -1) {
            printf("Invalid move! Please choose a valid piece.\n");
            return false;
        } else if (outer->pieces[piece].player != player) {
            printf("Invalid move! Please choose one of your own pieces.\n");
            return false;
        } else if (!charIsMoveable(outer, c)) {
            printf("Invalid move! Please choose a movable piece.\n");
            return false;
        } else if (!isValidLoc(outer, innerLocation)) {
            printf("Invalid move! A piece is already there.\n");
            return false;
        } else {
            int outerLocation = convertInputToIndex(innerLocation);
            movePiece(outer, c, outerLocation);
        }
    }



    return true;
}

bool movePiece(OuterBoard * outer, char c, int outerLocation) {
    // takes char and location, and makes move according to location
    outer->pieces[getPieceIndex(outer, c)].position = outerLocation;
}



void printBoard(OuterBoard * outer) {

    printf("-------------------\n");
    for (int row = 1; row < 6; ++row) {
        printf("| ");
        for (int column = 1; column < 6; ++column) {
            //
        }
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

