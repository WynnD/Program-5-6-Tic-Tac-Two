/* Wynn Drahorad
 * 9 am Tuesday lab
 * Program 5
 * Qt Creator, Windows 10
 */

#include <iostream>

using namespace std;

typedef struct piece {
    int player; // 1 for player one, 2 for player two
    int position = -1; // stores position of piece
    char c;
} piece_struct;

typedef struct innerBoard {
    // used to store where the inner board is located
    int current_position = 5; // position (1-9)
    int valid_locations[9] = {6,7,8,11,12,13,16,17,18};
} innerBoard_struct;

typedef struct OuterBoard {
    // holds inner_board, and all piece positions
    innerBoard * inner = new innerBoard;
    piece * pieces = (piece*) malloc(sizeof(piece)*8);
} OuterBoard_struct;

int getPieceIndex(OuterBoard * outer, char c) {
    // gets piece outer index
    for (int i = 0; i < 9; ++i) {
        if (outer->pieces[i].c == c) {
            return i;
        }
    }
    printf("Piece not found.\n");
    return -1;
}

int getGridLocation(OuterBoard * outer) {
    // returns location of the inner board
    return outer->inner->current_position;
}

void printHeader(char* progName) {
    // prints header
    cout << progName << endl
            << "Author: Wynn Drahorad" << endl
            << "Lab: Tues 9am" << endl
            << "System:  Windows 10, Qt IDE" << endl;

    return;
}

bool pipeComesAfter(OuterBoard * outer, int pos) {
    // checks if a pipe comes after the specified board position
    int inner_pos = outer->inner->current_position;
    int hasPipe[] = {1,2,6,7,11,12};
    if (inner_pos > 1) {
        if (inner_pos < 4) {
            for (int i = 0; i < 6; ++i) {
                hasPipe[i] = hasPipe[i]+(inner_pos-1);
            }
        }
        else if (inner_pos < 7) {
            for (int i = 0; i < 6; ++i) {
                hasPipe[i] = hasPipe[i]+5+(inner_pos-4);
            }
        } else {
            for (int i = 0; i < 6; ++i) {
                hasPipe[i] = hasPipe[i] + 10 + (inner_pos-7);
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        if (hasPipe[i] == pos) {
            return true;
        }
    }


    return false;
}

int convertInnerToOuter(OuterBoard * outer, int input) {
    // converts user inner board index (1-9) to outer board index (1-25)
    return outer->inner->valid_locations[input-1];
}

void setValidLocations(OuterBoard * outer, int validLocations[9][9]) {
    // sets valid locations upon update of grid location
    int gridLocation = getGridLocation(outer);
    for (int i = 0; i < 9; i++) {
        outer->inner->valid_locations[i] = validLocations[gridLocation-1][i];
    }

    return;
}

void initPieces(OuterBoard* board) {
    // initializes the player pieces and their position values to a default of -1
    for (int i = 0; i < 4; ++i) {
        board->pieces[i].c = 'A'+i;
        board->pieces[i].player = 1;

        board->pieces[i+4].c = 'a'+i;
        board->pieces[i+4].player = 2;

        board->pieces[i].position = board->pieces[i+4].position = -1;
    }

    return;
}

void printLocation(OuterBoard * outer, int outerLoc) {
    // prints the piece at given outerLoc, if no piece, prints . instead
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

    return;
}

bool moveBoard(OuterBoard* outer, int pos) {
    // moves board given new position
    outer->inner->current_position = pos;
    return true;
}

bool isOpenPosition(OuterBoard * outer, int location) {
    // checks if location is open (no piece already there) for a piece to be placed
    int posToGo;
    int checkPos;
    for (int i = 0; i < 9; ++i) {
        checkPos = outer->pieces[i].position;
        posToGo = convertInnerToOuter(outer, location);
        if (checkPos == posToGo) {
            printf("There is already a piece there. Please try again.\n");
            return false;
        }
    }

    return true;
}

bool charIsMoveable(OuterBoard * outer, char piece, int turn) {
    // checks if the given character is movable (must be within the boundaries of the board, or unused)

    if (turn < 5) {
        if (outer->pieces[getPieceIndex(outer, piece)].position != -1) {
            printf("Invalid move! You can move a previously-placed piece only after both players have placed 2 pieces.\n");
            return false;
        }
    }

    if (outer->pieces[getPieceIndex(outer, piece)].position == -1) {
        return true;
    }

    for (int i = 0; i < 9; ++i) {
        if (outer->inner->valid_locations[i] ==
                outer->pieces[getPieceIndex(outer, piece)].position)
            return true;
    }

    printf("Invalid move! Please choose a movable piece.\n");
    return false;
}

void movePiece(OuterBoard * outer, char c, int outerLocation) {
    // takes char and location, and makes move according to location
    outer->pieces[getPieceIndex(outer, c)].position = outerLocation;

    return;
}


int makeMove(OuterBoard * outer, int turn, int player,
              char c, int position, int successCode) {

    // makes move depending on given player, character, position, and previous success code

    /* EXPLANATION OF SUCCESS CODES
     * 0 = last move command failed
     * 1 = last move command was executed, piece was moved
     * 2 = board was moved successfully last move
     */

    if (tolower(c) == 'm') {
        if (turn < 5) {
            printf("Please wait until each player has played two pieces before moving the board.\n");
            return 0;
        } else if (successCode == 2) {
            printf("You cannot reposition the board immediately after your opponent has!\n");
            return 0;
        }
        if (position > 0 && position < 10) {
            moveBoard(outer, position);
            return 2;
        } else {
            printf("That is not a valid board location!");
            return 0;
        }
    } else {
        int piece = getPieceIndex(outer, c);
        if (piece == -1) {
            printf("Invalid move! Please choose a valid piece.\n");
            return 0;
        } else if (outer->pieces[piece].player != player) {
            printf("Invalid move! Please choose one of your own pieces.\n");
            return 0;
        } else if (!charIsMoveable(outer, c, turn)) {
            return 0;
        } else if (!isOpenPosition(outer, position)) {
            return 0;
        } else {
            int outerLocation = convertInnerToOuter(outer, position);
            movePiece(outer, c, outerLocation);
        }
    }



    return 1;
}

void printRemainingPieces(OuterBoard * outer, int player) {
    // prints remaining pieces, given player/owner

    piece * thePiece;

    printf("        Player %d:", player);


    for (int i = 4*(player-1); i < 4*player; ++i) {
        thePiece = &(outer->pieces[i]);
        printf(" ");
        if (thePiece->position == -1 && thePiece
                ->player == player) {
            printf("%c", thePiece->c);
        } else {
            printf(" ");
        }
    }

    printf("\n");

    return;
}

void printPieceRow(OuterBoard * outer, int row) {
    // prints given row (these rows contain pieces and pipes [borders])

    printf("|");
    for (int column = 1+row*5; column < 6+row*5; ++column) {
        printLocation(outer, column);
        if (pipeComesAfter(outer, column)) {
            printf("|");
        } else if (column != 5+row*5) {
            printf(" ");
        }
    }

    printf("|");
    // print remaining pieces
    if (row == 0) {
        printf("    Pieces remaining for: \n");
    } else
    if (row == 1) {
        printRemainingPieces(outer, row+1);
    } else
    if (row == 3) {
        printf("       4 5 6\n");
    } else {
        printf("\n");
    }
}


void printHorizontalBorder(OuterBoard * outer, int row) {
    // prints Horizontal border row depending on inner_board location

    int inner_pos = outer->inner->current_position;
    printf("|");
    if (row == 1) {
        switch(inner_pos) {
            case 1:
                printf(" ---------         ");
                break;
            case 2:
                printf("     ---------     ");
                break;
            case 3:
                printf("         --------- ");
                break;
            default:
                printf("                   ");
                break;
        }
        printf("|");
        printRemainingPieces(outer, 1);

    } else if (row == 2) {
        switch(inner_pos) {
            case 1:
                printf(" ---------         ");
                break;
            case 2:
                printf("     ---------     ");
                break;
            case 3:
                printf("         --------- ");
                break;
            case 4:
                printf(" ---------         ");
                break;
            case 5:
                printf("     ---------     ");
                break;
            case 6:
                printf("         --------- ");
                break;
            default:
                printf("                   ");
                break;
        }

        printf("|\n");

    } else if (row == 3) {
        switch(inner_pos) {
            case 4:
                printf(" ---------         ");
                break;
            case 5:
                printf("     ---------     ");
                break;
            case 6:
                printf("         --------- ");
                break;
            case 7:
                printf(" ---------         ");
                break;
            case 8:
                printf("     ---------     ");
                break;
            case 9:
                printf("         --------- ");
                break;
            default:
                printf("                   ");
                break;
        }
        printf("|       1 2 3\n");
    } else if (row == 4) {
        switch(inner_pos) {
            case 7:
                printf(" ---------         ");
                break;
            case 8:
                printf("     ---------     ");
                break;
            case 9:
                printf("         --------- ");
                break;
            default:
                printf("                   ");
        }
        printf("|       7 8 9\n");
    }

    return;
}

void printBoard(OuterBoard * outer) {
    // prints board using printPieceRow() and printHorizontalBorder()

    printf(" ------------------- \n");
    for (int row = 0; row < 5; ++row) {
        printPieceRow(outer, row);
        if (row < 4) {
            printHorizontalBorder(outer, row+1);
        }
    }

    printf(" ------------------- \n");

}

int whoOwnsPosition(OuterBoard* outer, int outerPosition) {
    // returns player that owns given outerPosition
    for (int i = 0; i < 8; ++i) {
        if (outer->pieces[i].position == outerPosition) {
            return outer->pieces[i].player;
        }
    }
    return -1;
}

int queryPlayerChar(int turn, int player) {
    // asks player for move character

    char moveChar;
    cout << turn << ". Player " << player << ": Enter piece to move and destination number, or 'm'"
            << endl << "to move the grid and move direction (1-9 except 5): ";
    scanf(" %c", &moveChar);
    return moveChar;
}

int queryPlayerInt() {
    // asks player for integer, corresponding to position to move

    int moveInt;
    scanf(" %d", &moveInt);
    return moveInt;
}
/*
bool isValid(OuterBoard * outer, int position) {
    for (int i = 0; i < 9; i++) {
        if (position == outer->inner->valid_locations[i]) {
            return true;
        }
    }
    return false;
}
*/

int isWin(OuterBoard * outer) {
    // checks if current board has a winner

    //
    int winners[8][3] = // diagonal win combinations
                 {{outer->inner->valid_locations[2],
                   outer->inner->valid_locations[4],
                   outer->inner->valid_locations[6]},
                  {outer->inner->valid_locations[0],
                   outer->inner->valid_locations[4],
                   outer->inner->valid_locations[8]},

                  // horizontal win combinations
                  {outer->inner->valid_locations[0],
                   outer->inner->valid_locations[1],
                   outer->inner->valid_locations[2]},
                  {outer->inner->valid_locations[3],
                   outer->inner->valid_locations[4],
                   outer->inner->valid_locations[5]},
                  {outer->inner->valid_locations[6],
                   outer->inner->valid_locations[7],
                   outer->inner->valid_locations[8]},

                  // vertical win combinations
                  {outer->inner->valid_locations[0],
                   outer->inner->valid_locations[3],
                   outer->inner->valid_locations[6]},
                  {outer->inner->valid_locations[1],
                   outer->inner->valid_locations[4],
                   outer->inner->valid_locations[7]},
                  {outer->inner->valid_locations[2],
                   outer->inner->valid_locations[5],
                   outer->inner->valid_locations[8]}};

    int counterPlayer1;
    int counterPlayer2;
    for (int i = 0; i < 8; ++i) {
        // check each win condition (8 different combinations)
        counterPlayer1 = counterPlayer2 = 0;
        for (int j = 0; j < 3; ++j) {
            // check which player owns the position
            if (whoOwnsPosition(outer,winners[i][j]) == 1) {
                ++counterPlayer1;
            }

            if (whoOwnsPosition(outer,winners[i][j]) == 2) {
                ++counterPlayer2;
            }
        }

        // if either player has all three positions in one win condition, return winning player
        if (counterPlayer1 == 3) {
            return 1;
        }
        if (counterPlayer2 == 3) {
            return 2;
        }

    }

    return 0;
}

int main()
{
    int winner = 0;
    OuterBoard * outer = new OuterBoard;
    int player = 1;
    int turn = 1;
    int moveInt;
    char moveChar;
    int moveSuccessful;
    char progName[] = "Program 5: Tic Tac Two";
    int validLocations[9][9] = {{1,2,3,6,7,8,11,12,13},
                                {2,3,4,7,8,9,12,13,14},
                                {3,4,5,8,9,10,13,14,15},
                                {6,7,8,11,12,13,16,17,18},
                                {7,8,9,12,13,14,17,18,19},
                                {10,11,12,15,16,17,20,21,22},
                                {11,12,13,16,17,18,21,22,23},
                                {12,13,14,17,18,19,22,23,24},
                                {13,14,15,18,19,20,23,24,25}};

    // begin run program
    printHeader(progName); // print header
    initPieces(outer); // initialize pieces (set their characters and initial positions)

    setValidLocations(outer, validLocations);
    printBoard(outer);
    while(!winner) {
        // continue to loop while winner equals 0 (and/or is false)
        moveChar = queryPlayerChar(turn, player); // get move character
        moveInt = queryPlayerInt(); // get position to move to
        moveSuccessful = makeMove(outer, turn, player, // make move, and check if move successful
                                  moveChar, moveInt, moveSuccessful);
        if (moveSuccessful > 0) {
            // if move successful, iterate turn and toggle player
            turn++;
            player = (player % 2) + 1;
        }

        setValidLocations(outer, validLocations); // update list of valid location
        winner = isWin(outer); // check if win condition met
        printBoard(outer); // print board
    }

    printf("\n\nCongratulations to player %d! You won!\n\n", winner);


    return 0;
}

