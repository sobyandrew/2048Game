#include <iostream>
#include <iomanip>
using namespace std;

//has these as defined variables so you can change the board size as wanted
#define BOARD_COLUMNS 4
#define BOARD_ROWS  4

//create a board for 2048
int board [BOARD_ROWS][BOARD_COLUMNS] = {0};

//this function will populate the board with a 2 after a move randomly placed on the board
void populateBoard(){
    int emptySpaces = 0;
    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++){
            if(board[i][j] == 0) emptySpaces++;//found an empty space to place a 2
        }
    }

    if(emptySpaces == 0) return;//if there are no spaces that are empty then return as no where to place

    int random = rand() % emptySpaces; //use this to find a random placement within the spaces
    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++){
            if(board[i][j] == 0){
                emptySpaces--;
                if(emptySpaces == random) {
                    board[i][j] = 2; //place the two if random and empty spaces equal each other
                    return;
                }
            }
        }
    }
}

//initialize the board with all 0's just incase the above statement doesnt work.
void boardinit(){
    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++){
            board[i][j] = 0;
        }
    }
    populateBoard();
}

//print out the board
void printBoard(){
    for(int i = 0; i < BOARD_COLUMNS; i++){
        cout << " ------";
    }
    cout << endl;
    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++){
            cout <<"|" << setfill(' ') << setw(5) << board[i][j] << " ";
        }
        cout <<"|" <<endl;
    }

    for(int i = 0; i < BOARD_COLUMNS; i++){
        cout << " ------";
    }
    cout << endl;
}

//check if the board has any playable options if not the player has lost
bool boardPlayable(){
    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++){
            if(board[i][j] == 0) return true;
            if(i - 1 >= 0){
                if(board[i][j] == board[i-1][j]){
                    return true;
                }
            }
            if(i + 1 < BOARD_COLUMNS){
                if(board[i][j] == board[i+1][j]){
                    return true;
                }
            }
            if(j - 1 >= 0){
                if(board[i][j] == board[i][j-1]){
                    return true;
                }
            }
            if(j + 1 < BOARD_ROWS){
                if(board[i][j] == board[i][j+1]){
                    return true;
                }
            }
        }
    }
    printBoard();
    cout << "You have lost the game! Restart the program to try again." << endl;
    return false;
}


//this function moves the tiles in the desired direction to pull them together for combination or clean up after a
//combination
void moveTiles(char move){
    if(move == 'w' || move == 'W'){ // this is to move up
        for(int i = 0; i < BOARD_ROWS; i++){
            for(int j = 0; j < BOARD_COLUMNS; j++) {
                int position = i;
                if (board[i][j] == 0) { // check rest of row to see if we can replace
                    int position2 = position;
                    while((position2 < BOARD_ROWS) && board[i][j] == 0){
                        if(board[position2][j] != 0 ){
                            board[i][j] = board[position2][j];
                            board[position2][j] = 0;
                            break;
                        }
                        position2++;
                    }
                }
            }
        }
    }
    if(move == 's' || move == 'S') { //this is to move tiles down
        for(int i = BOARD_ROWS-1; i >= 0; i--){
            for(int j = BOARD_COLUMNS-1; j >= 0; j--){
                int position = i - 1;
                if (position >= 0) {
                    if (board[i][j] == 0) {
                        int position2 = position;
                        while ((position2 >= 0) && board[i][j] == 0) {
                            if (board[position2][j] != 0) {
                                board[i][j] = board[position2][j];
                                board[position2][j] = 0;
                                break;
                            }
                            position2--;
                        }
                    }
                }
            }
        }
    }

    if(move == 'd' || move == 'D'){//move right
        for(int i = BOARD_ROWS-1; i >= 0; i--){
            for(int j = BOARD_COLUMNS-1; j >= 0; j--){
                int position = j-1;
                if(position >= 0){
                    if(board[i][j] == 0){
                        int position2 = position;
                        while((position2 >= 0) && board[i][j] == 0){
                            if(board[i][position2] != 0 ){
                                board[i][j] = board[i][position2];
                                board[i][position2] = 0;
                                break;
                            }
                            position2--;
                        }
                    }
                }
            }
        }
    }

    if(move == 'a' || move == 'A'){
        for(int i = 0; i < BOARD_ROWS; i++){
            for(int j = 0; j < BOARD_COLUMNS; j++){
                int position = j+1;
                if(position < BOARD_ROWS){
                    if(board[i][j] == 0){
                        int position2 = position;
                        while((position2 < BOARD_ROWS) && board[i][j] == 0){
                            if(board[i][position2] != 0 ){
                                board[i][j] = board[i][position2];
                                board[i][position2] = 0;
                                break;
                            }
                            position2++;
                        }
                    }
                }
            }
        }
    }
}

//combine tiles from the direction entered
void combineTiles(char move){
    if(move == 'w' || move == 'W') { // this is to combine up
        for (int i = 0; i < BOARD_ROWS-1; i++) {
            for (int j = 0; j < BOARD_COLUMNS; j++) {
                int positionBelow = i + 1;
                if (board[i][j] == board[positionBelow][j]) {
                    board[i][j] *= 2;
                    board[positionBelow][j] = 0;
                }
            }
        }
    }

    if(move == 's' || move == 'S') { // this is to combine down
        for (int i = BOARD_ROWS - 1; i >= 0; i--) {
            for (int j = BOARD_COLUMNS - 1; j >= 0; j--) {
                int position = i - 1;
                if (position >= 0) {
                    if (board[i][j] == board[position][j]) {
                        board[i][j] += board[position][j];
                        board[position][j] = 0;
                    }
                }
            }
        }
    }

    if(move == 'd' || move == 'D') { // this is to combine right
        for (int i = BOARD_ROWS - 1; i >= 0; i--) {
            for (int j = BOARD_COLUMNS - 1; j >= 0; j--) {
                int position = j - 1;
                if (position >= 0) {
                    if (board[i][j] == board[i][position]) {
                        board[i][j] += board[i][position];
                        board[i][position] = 0;
                    }
                }
            }
        }
    }

    if(move == 'a' || move == 'A'){ // this is to combine left
        for(int i = 0; i < BOARD_ROWS; i++){
            for(int j = 0; j < BOARD_COLUMNS; j++){
                int position = j+1;
                if(position < BOARD_ROWS){
                    if(board[i][j] == board[i][position]){
                        board[i][j] += board[i][position];
                        board[i][position] = 0;
                    }
                }
            }
        }
    }
}

//this will make a move depending on the input from the user
void makeMove(char move){
    int board2[BOARD_ROWS][BOARD_COLUMNS]={0};
    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++) {
           board2[i][j] = board[i][j];
        }
    }
    moveTiles(move);
    combineTiles(move);
    moveTiles(move);

    for(int i = 0; i < BOARD_ROWS; i++){
        for(int j = 0; j < BOARD_COLUMNS; j++) {
            if(board2[i][j] != board[i][j]){
                populateBoard();
                return;
            }
        }
    }
}

void startGame(){
    boardinit();
    char move;
    bool playGame = true;
    while(playGame){
        printBoard();
        cout << endl <<"Enter a move w = UP, s = DOWN, a = LEFT, d = RIGHT, then enter to confirm." << endl;
        cin >> move;
        makeMove(move);
        playGame = boardPlayable();
    }
}

int main() {
    cout << "Welcome to 2048!" << endl;
    startGame();
    return 0;
}