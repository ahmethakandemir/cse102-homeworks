#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct  // this is the struct that i keep the boards information.
{
    int tiles[3][3];
    int moves;
    int blank_row;
    int blank_col;
    int score;
    int best_score;

} boardType;
boardType board;
int isinarray(int num){ // this function is used in shuffle() function to know if an random added number is already in board array or not.
    for (int i = 0; i < 3; i++){
        for(int k = 0;k < 3;k++){
            if (board.tiles[i][k] == num) {
                return 1;
            }
        }
    }
    return 0;
}

int isSolvable(int puzzle[3][3]) { // in 8 puzzle game, not every random generated boards are solvable in terms of game rules. so you need to look the inversions and calculate something to find out if a board is solvable or not
    int inversions = 0;            // the thing i am adding to, at the end, if inversions count is odd, puzzle is solvable, else it is not.
    int flat_puzzle[9];

    
    for (int i = 0; i < 3; i++) {  // Flattening the puzzle board into a 1D array
        for (int j = 0; j < 3; j++) {
            flat_puzzle[i * 3 + j] = puzzle[i][j];
        }
    }

    
    for (int i = 0; i < 9; i++) {   // Count the number of inversions
        for (int j = i + 1; j < 9; j++) {
            if (flat_puzzle[i] != 0 && flat_puzzle[j] != 0 && flat_puzzle[i] > flat_puzzle[j]) {
                inversions++;
            }
        }
    }

    
    if (inversions % 2 == 0) {  // Check if the puzzle is solvable
        return 1;  // Solvable
    } else {
        return 0;  // Not solvable
    }
}

int shuffle(){  // shuffling the board when restarting it.
    for(int i = 0;i < 3;i++){
        for(int k = 0;k < 3;k++){
            board.tiles[i][k] = 0;
        }
    }
    int num;
    for(int i = 0;i < 3;i++){
        for(int k = 0;k < 3;k++){
            if(i == 2 && k == 2){
                break;
            }
            while(1){
                num = random()%8 + 1;
                if(!isinarray(num)){    // checking to not place duplicated numbers on the board.
                    break;
                }
            }
            board.tiles[i][k] = num;
        }
    }
    board.moves = 0;    // reseting the counter when shuffling the game board.
    board.blank_col = 2;
    board.blank_row = 2;
    if(isSolvable(board.tiles)){    // if the puzzle is solvable, we are getting to play it
        return 1;
    }
    else{
        shuffle();                  // else i made a recursion to shuffle it again.
    }
    return 0;
}

int drawBoard(){                // drawing the board basically.
    system("clear");            // i used this system("clear"), to show the latest sitoation of the board in terminal window.
    FILE * boardfile;
    boardfile = fopen("board.txt","a+");
    for(int i = 0;i < 3;i++){
        for(int k = 0;k < 3;k++){
            if(board.tiles[i][k] == 0){ // 0 means the blank = '_'
                printf("_ ");
                fprintf(boardfile,"_ ");
            }
            else{
                printf("%d ",board.tiles[i][k]);
                fprintf(boardfile,"%d ",board.tiles[i][k]);
            }
        }
        printf("\n");
        fprintf(boardfile,"\n");
    }
    printf("-----\n");
    fprintf(boardfile,"-----\n");
    fclose(boardfile);
    return 0;
}

int checkStatus(){  // checking if the game is finished or not.
    int checker = 1;
    for(int i = 0;i < 3; i++){
        for(int k = 0; k < 3; k++){
            if(k == 2 && i == 2){
                checker = 0;
            }
            if(board.tiles[i][k] != checker){
                return 0;
            }
            else{
                checker++;
            }
        }
    }
    printf("Congratulations!!!\n"); // congratulatory message..
    return 1;

}

int islegal(int movement, char direction) { //  checking the moves if they are legal or not.
    int tempi, tempk;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (movement == board.tiles[i][k]) { // we are getting the number's coordinates that the user wants to move to any direction
                tempi = i;
                tempk = k;
            }
        }
    }
    // checking all the possibilities.
    if (direction == 'D' && tempi < 2 && board.tiles[tempi + 1][tempk] == 0) {
        return 1;
    } else if (direction == 'U' && tempi > 0 && board.tiles[tempi - 1][tempk] == 0) {
        return 1;
    } else if (direction == 'R' && tempk < 2 && board.tiles[tempi][tempk + 1] == 0) {
        return 1;
    } else if (direction == 'L' && tempk > 0 && board.tiles[tempi][tempk - 1] == 0) {
        return 1;
    } else {
        return 0;
    }
}

void scoring(int cases){    // printing the score to text file and terminal, it depends on if the user played it or the computer, so i made it with a parameter.
    FILE * scores;
    scores = fopen("scores.txt","a+");
    if(cases == 1){
        printf("\n Total number of moves : %d\n",board.moves);
        board.score = 1000 - (board.moves * 10);
        printf("Your Score: %d\n", board.score);
        if(board.score > board.best_score){
            board.best_score = board.score;
            fprintf(scores,"%d\n",board.score);
        }
    }
    else if(cases == 2){
        printf("\nTotal number of computer moves : %d\n",board.moves);
    }
    fclose(scores);
}

int gameplay(){ // function that the moves made.

    int movement;
    char direction;
    while(1){   //  while loop for the iteration of prompting until the user enters a legal move.
        printf("\nEnter your move: ");
        scanf("%d-%c",&movement,&direction);
        getchar();
        //printf("%d-%c",movement,direction);
        if (islegal(movement,direction)){
            break;
        }
        else{
            printf("\nPlease enter a legal move!!!:");
            
        }
    }
    int itemp,ktemp;
    for(int i = 0;i < 3;i++){
        for(int k = 0; k < 3;k++){
            if(movement == board.tiles[i][k]){  // we are getting the number's coordinates that the user wants to move to any direction
                itemp = i;
                ktemp = k;
            }
        }
    }
    board.tiles[itemp][ktemp] = 0;  // making the moved number equal to 0, which means blank = '_'
                                    // and making the blank equal to number that user entered so they're switched
    if(direction == 'R'){
        board.tiles[itemp][ktemp + 1] = movement;   
        board.blank_col--;
    }
    else if(direction == 'L'){
        board.tiles[itemp][ktemp - 1] = movement;
        board.blank_col++;
    }
    else if(direction == 'U'){
        board.tiles[itemp - 1][ktemp] = movement;
        board.blank_row--;
    }
    else if(direction == 'D'){
        board.tiles[itemp + 1][ktemp] = movement;
        board.blank_row++;
    }
    board.moves++;              // incrementing the move counter.
    drawBoard();                // drawing the board to the text file and the terminal.
    if(checkStatus()){
        return 2;
    }
    else{
        gameplay();             // recursive if the game didn't finished.
    }
    return 0;
}

int autoPlay(){                 // function that the pc plays the game.
    FILE * boardfile;

    int movement,directpicker;
    char direction;
    while(1){        
        movement = random()%8 + 1;                              // generating random numbers.
        while(movement == 1 && board.tiles[0][0] == 1){         // this and the while loop at the below might be confusing, it is just used to speed up the process,
            movement = random()%8 + 1;
        }
        while(movement == 3 && board.tiles[0][2] == 3){         // this loops used for if the 1 and 3 is in their places, do not touch them because if the pc changes their locations again and again, it can take millions of moves to solve the puzzle
            movement = random()%8 + 1;
        }
                                                                // the rest is going randomly.
        directpicker = random()%4 + 1;                          // generating random directions.
        switch (directpicker){
        case 1:
            direction = 'R';
            break;
        case 2:
            direction = 'L';
            break;
        case 3:
            direction = 'U';
            break;
        case 4:
            direction = 'D';
            break;
        default:
            break;
        }

        if(islegal(movement,direction)){                    // check if the random generated number-direction move is legal or not.
            break;
        }
    }
    int itemp,ktemp;
    for(int i = 0;i < 3;i++){
        for(int k = 0; k < 3;k++){
            if(movement == board.tiles[i][k]){
                itemp = i;
                ktemp = k;
            }
        }
    }
    board.tiles[itemp][ktemp] = 0;
                                                            // making the moves.
    if(direction == 'R'){
        board.tiles[itemp][ktemp + 1] = movement;
        board.blank_col--;
    }
    else if(direction == 'L'){
        board.tiles[itemp][ktemp - 1] = movement;
        board.blank_col++;
    }
    else if(direction == 'U'){
        board.tiles[itemp - 1][ktemp] = movement;
        board.blank_row--;
    }
    else if(direction == 'D'){
        board.tiles[itemp + 1][ktemp] = movement;
        board.blank_row++;
    }
    board.moves++;
    boardfile = fopen("board.txt","a+");
    fprintf(boardfile,"Computer Move = %d-%c\n",movement,direction);
    printf("Computer Move = %d-%c\n",movement,direction);
    fclose(boardfile);

    drawBoard();    // drawing the board.
    
    if(checkStatus()){
        return 2;
    }
    else{
        //sleep(1);
        //printf("%d",board.moves);
        autoPlay();     // if the game is not finished, recursively repeat.
    }

    return -1;
}

int main(){
    srand(time(NULL));  // to make random moves.
    while(1){

    int selection = 0;
    printf("\nwelcome to the 8 puzzle game!!\n");
    printf("1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n");
    printf("\nPlease select an option: ");
    scanf("%d",&selection);
    while(getchar() != '\n'); 
    switch (selection){
        case 1:
            shuffle();
            drawBoard();
            gameplay();
            scoring(1);
            break;
        case 2:
            shuffle();
            drawBoard();
            autoPlay();
            scoring(2);
            break;
        case 3:
            printf("The best score is: %d\n",board.best_score);
            break;
        case 4:
            return 0;
        default:
            printf("wrong selection!!\n");
            break;
        }
        
    }
}