#include <stdio.h>
#include <time.h>
#include <stdlib.h>
FILE * boardfile;


typedef struct
{
    int tiles[3][3];
    int moves;
    int blank_row;
    int blank_col;

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
    boardfile = fopen("board.txt","w");

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
    fclose(boardfile);
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
int islegal(int movement,char direction){
    int tempi,tempk;
    for(int i = 0;i < 3; i++){
        for(int k = 0; k < 3; k++){
            if(movement == board.tiles[i][k]){
                tempi = i;
                tempk = k;
            }
        }
    }

    if(((board.blank_row == tempi + 1 && movement == 'D') || (board.blank_row == tempi - 1 && movement == 'U')) &&  ((board.blank_col == tempk + 1 && movement == 'R') || (board.blank_col == tempk - 1 && movement == 'L'))){
        return 1;
    }
    else{
        return 0;
    }
}

int gameplay(){

    int movement;
    char direction;
    while(1){
        printf("\nEnter your move: ");
        scanf("%d-%c",&movement,&direction);
        getchar();
        printf("%d-%c",movement,direction);
        if (islegal(movement,direction)){
            break;
        }
        else{
            printf("\nPlease enter a legal move!!!:");
            
        }
    }

    drawBoard();
    
    if(checkStatus()){
        printf("\n move counter is : %d\n",board.moves);
        return 2;
    }



    return 0;
}

int main(){

    shuffle();

    drawBoard();

    gameplay();

}
