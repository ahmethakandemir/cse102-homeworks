#include <stdio.h>

int part3();
int drawingBoard(int,int,char);
int check();
int again();


int player = 2;
int board[3][3] = {0};


int main(){
    part3();
}

int part3(){
    char p,move;
    int x,y;
    drawingBoard(x,y,move);
    while(1)
    {
    if(player % 2 == 1){
        move = 'o';
    }
    else{
        move = 'x';
    }

        printf("Player %d's Turn(%c): ", player % 2 + 1,move);
        while(1){
            scanf("%d %d",&x,&y);
            if((x >= 0 && x <= 2) && (y >= 0 && y <= 2)){
                break;
            }
            printf("please enter valid numbers!!: \n");
            getchar();
        }

        drawingBoard(x,y,move);
        player++;

        if(check()){
            if(!again()){
                return 0;
            }
        }
        
        
    }
    return 0;
}

int again(){
    char secim;
    for(int i = 0; i < 3; i++){
        for(int k = 0; k < 3; k++){
            board[i][k] = 0;
        }
    }
    printf("\ndo you want to play again??: ");
    if(scanf(" %c",&secim) == 1){
        switch (secim)
        {
        case 'y':case 'Y':
            return 1;
            break;
        case 'n':case 'N':
            return 0;
        default:
            printf("\ninvalid input!");
            again();
        }
        
    }
    return 0;
}   


int drawingBoard(int i,int k,char type){
    printf("\n");
    if(board[i][k] == 0){
        board[i][k] = type;
    }
    else{
        printf("entered wrong location!\n");
        player--;
    }
    for(int i = 0; i < 3; i++){
        for(int k = 0; k < 3; k++){
            if(board[i][k] == 0){
                printf("_ ");
            }
            else{
                printf("%c ",board[i][k]);
            }
        }
        printf("\n");
    }

    printf("\n");
    return 1;
}

int check(){
    for(int i = 0; i < 3; i++){

        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
        
            if(board[i][0] == 120){
                printf("\nPlayer 1 won!!\n");
                return 1;
            }
            else if(board[i][0] == 111){
                printf("Player 2 won!!");
                return 1;
            }
        }
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
        
            if(board[0][i] == 120){
                printf("\nplayer 1 won!!\n");
                return 1;
            }
            else if(board[0][i] == 111){
                printf("player 2 won!!");
                return 1;
            }
        }
    }
    int sum = 0;
    for(int i = 0;i < 3;i++){
        sum += board[i][i];
    }
    if(sum == 333){
        printf("player 2 won!!");
        return 1;
    }
    else if(sum == 360){
        printf("player 1 won!!");
        return 1;
    }
    sum = 0;
    sum = board[2][0] + board[1][1] + board [0][2];
    if(sum == 333){
        printf("player 2 won!!");
        return 1;
    }
    else if(sum == 360){
        printf("player 1 won!!");
        return 1;
    }
    for(int i = 0; i< 3; i++){
        for(int k = 0; k < 3; k++){
            if(board[i][k] == 0){
                return 0;
            }
        }
    }
    return 1;
}