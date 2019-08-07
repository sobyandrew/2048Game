#include <iostream>
#include <iomanip>
using namespace std;

//has these as defined variables so you can change the board size as wanted
#define BOARD_COLUMNS 4
#define BOARD_ROWS  4

//create a board for 2048
int board [BOARD_COLUMNS][BOARD_ROWS] = {0};

//this function will populate the board with a 2 after a move randomly placed on the board
void populateBoard(){
    int emptySpaces = 0;
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
            if(board[i][j] == 0) emptySpaces++;//found an empty space to place a 2
        }
    }

    if(emptySpaces == 0) return;//if there are no spaces that are empty then return as no where to place

    int random = rand() % emptySpaces; //use this to find a random placement within the spaces
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
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
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
            board[i][j] = 0;
        }
    }
    populateBoard();
}

//check if the board has any playable options if not the player has lost
bool boardPlayable(){
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
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
    cout << "You have lost the game! Restart the program to try again.";
    return false;
}

//print out the board
void printBoard(){
    for(int i = 0; i < BOARD_COLUMNS; i++){
        cout << " ------";
    }
    cout << endl;
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
            cout <<"|" << setfill(' ') << setw(5) << board[i][j] << " ";
        }
        cout <<"|" <<endl;
    }

    for(int i = 0; i < BOARD_COLUMNS; i++){
        cout << " ------";
    }
    cout << endl;
}

//this will make a move depending on the input from the user
void makeMove(char move){
    int board2[BOARD_ROWS][BOARD_COLUMNS]={0};
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++) {
           board2[i][j] = board[i][j];
        }
    }
    if(move == 'w' || move == 'W'){
        for(int i = 0; i < BOARD_COLUMNS; i++){
            for(int j = 0; j < BOARD_ROWS; j++){
                int position = j+1;
                if(position < BOARD_ROWS){
                    if(board[j][i] == board[position][i]){
                        board[j][i] += board[position][i];
                        board[position][i] = 0;
                    }
                    if(board[j][i] == 0){
                        int position2 = position;
                        while((position2 < BOARD_ROWS) && board[j][i] == 0){
                            if(board[position2][i] != 0 ){
                                board[j][i] = board[position2][i];
                                board[position2][i] = 0;
                                break;
                            }
                            position2++;
                        }

                    }
                }
            }
        }
    }
    if(move == 'd' || move == 'D'){
        for(int i = BOARD_COLUMNS-1 ; i >= 0; i--){
            for(int j = BOARD_ROWS - 1; j >= 0; j--){
                int position = j-1;
                if(position >= 0){
                    if(board[i][j] == board[i][position]){
                        board[i][j] += board[i][position];
                        board[i][position] = 0;
                    }
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
        for(int i = 0; i < BOARD_COLUMNS; i++){
            for(int j = 0; j < BOARD_ROWS; j++){
                int position = j+1;
                if(position < BOARD_ROWS){
                    if(board[i][j] == board[i][position]){
                        board[i][j] += board[i][position];
                        board[i][position] = 0;
                    }
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
    if(move == 's' || move == 'S'){
        for(int i = BOARD_COLUMNS-1 ; i >= 0; i--){
            for(int j = BOARD_ROWS - 1; j >= 0; j--){
                int position = j-1;
                if(position >= 0){
                    if(board[j][i] == board[position][i]){
                        board[j][i] += board[position][i];
                        board[position][i] = 0;
                    }
                    if(board[j][i] == 0){
                        int position2 = position;
                        while((position2 >= 0) && board[j][i] == 0){
                            if(board[position2][i] != 0 ){
                                board[j][i] = board[position2][i];
                                board[position2][i] = 0;
                                break;
                            }
                            position2--;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < BOARD_COLUMNS; i++){
        for(int j = 0; j < BOARD_ROWS; j++) {
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