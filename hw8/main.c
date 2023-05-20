#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
FILE * boardfile;


typedef struct
{
    int tiles[3][3];
    int moves;
    int blank_row;
    int blank_col;
    int score;
    int best_score;
} boardType;
boardType board;


int isinarray(int num){
    for (int i = 0; i < 3; i++){
        for(int k = 0;k < 3;k++){
            if (board.tiles[i][k] == num) {
                return 1;
            }
        }
    }
    return 0;
}

int shuffle(){
    int num;
    srand(time(NULL));

    for(int i = 0;i < 3;i++){
        for(int k = 0;k < 3;k++){
            if(i == 2 && k == 2){
                break;
            }
            while(1){
                num = random()%8 + 1;
                if(!isinarray(num)){
                    break;
                }
            }
            board.tiles[i][k] = num;

        }
    }
    board.moves = 0;
    board.blank_col = 2;
    board.blank_row = 2;
    return 1;
}

int drawBoard(){
    //boardfile = fopen("board.txt","w");
    printf("\n");
    for(int i = 0;i < 3;i++){
        for(int k = 0;k < 3;k++){
            if(board.tiles[i][k] == 0){
                printf("_ ");
            }
            else{
                printf("%d ",board.tiles[i][k]);        // change to fprintf;;;;;
            }
        }
        printf("\n");
    }
    printf("\n\n");
    //fclose(boardfile);
    return 0;
}

int checkStatus(){
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
    return 1;

}
int islegal(int movement, char direction) {
    int tempi, tempk;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (movement == board.tiles[i][k]) {
                tempi = i;
                tempk = k;
            }
        }
    }

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
void scoring(int cases){
    if(cases == 1){
        printf("\n mTotal number of moves : %d\n",board.moves);
        board.score = 1000 - (board.moves * 10);
        printf("Your Score: %d\n", board.score);
        if(board.score > board.best_score){
            board.best_score = board.score;
        }
    }
    else if(cases == 2){
        printf("\n mTotal number of computer moves : %d\n",board.moves);
    }

}
int gameplay(){

    int movement;
    char direction;
    while(1){
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
            if(movement == board.tiles[i][k]){
                itemp = i;
                ktemp = k;
            }
        }
    }
    board.tiles[itemp][ktemp] = 0;

    //printf("movement is %d, itemp is: %d, ktemp is: %d\n",movement,itemp,ktemp);

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
    drawBoard();
    
    if(checkStatus()){
        return 2;
    }
    else{
        gameplay();
    }



    return 0;
}

int autoPlay(){
    
    int movement,directpicker;
    char direction;
    while(1){
        movement = random()%8 + 1;
        directpicker = random()%4 + 1;
        switch (directpicker)
        {
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

        if(islegal(movement,direction)){
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

    //printf("movement is %d, itemp is: %d, ktemp is: %d\n",movement,itemp,ktemp);

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
    drawBoard();
    
    if(checkStatus()){
        return 2;
    }
    else{
        //sleep(1);
        printf("%d",board.moves);
        autoPlay();
    }

    return -1;
}

int main(){
    srand(time(NULL));
    board.best_score = -9999;
    while(1){

    int selection = 0;
    printf("\nwelcome to the 8 puzzle game!!\n");
    printf("Please select an option:\n");
    printf("1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n");
    while (!(selection >= 1 && selection <= 4)){
        scanf("%d",&selection);
        getchar();
    }
    switch (selection){
    case 1:
        shuffle();
        drawBoard();
        gameplay();
        scoring(1);
    case 2:
        shuffle();
        drawBoard();
        autoPlay();
        scoring(2);
    case 3:
        printf("The best score is: %d",board.best_score);
    default:
        break;
    }
    

    }
}
