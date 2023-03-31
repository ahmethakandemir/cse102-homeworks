#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int flag = 0,n = 1,d = 0,c = 0,counter,sayac = 0;
int drawing(int flag,int c,int n,int sayac);
void gameplay(int c,int n);
int status(int c,int d);
int game();

int main(){

    game();    

}

int drawing(int flag,int c,int n,int sayac){
        
    if(flag == 0){
        srand(time(NULL));
            printf("Enter board size: ");
            scanf("%d",&n);
        while((n < 5) || (n > 10)){
            printf("'n' can't be less than 2, enter n value again: ");
            scanf("%d",&n);
        }
        while(c == d){
            c = rand()%(n*n);
            d = rand()%(n*n);
        }
    }

    counter = 0;
    
    if(status(c,d)){
        printf("************************\n\nYOU WON!!(in %d moves!!)\n\n************************\n",sayac);
        return 1;
    }
    for(int i = 0; i < (2*n)+1; i++){
        printf("-");
    }
    
    for(int i = 0; i < n;i++){
        printf("\n");
        for(int k = 0; k < n;k++){
            if (counter == d){
                printf("|D");
            }
            else if(counter == c){
                printf("|C");
            }
            else{
                printf("| ");
            }
            counter++;
            
        }
        printf("|");
    }
    printf("\n");
    for(int i = 0; i < (2*n)+1; i++){
        printf("-");
    }
    sayac++;
    printf("\n");
    flag = 1;
    
    gameplay(c,n);

    return 1;
}


int status(int c,int d){
    if(c == d){
        return 1;
    }
    return 0;
}


void gameplay(int c,int n){
    char input;
    
    printf("enter your move: ");
    scanf(" %c",&input);
    system("clear");
    switch (input)
    {
    case 'w':
        if(c >= n){
            c = c - n;
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    case 's':
        if (c + n < n * n){
            c = c + n;
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    case 'a':
        if (c % n > 0){
            c = c - 1;
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    case 'd':
        if (c % n < n - 1){
            c = c + 1;
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    default:
        printf("invalid movement key pressed, try again!!\n");
        break;
    }
    sayac++;
    drawing(1,c,n,sayac);
}

int game(){
    int selection;
    system("clear");
    printf("Welcome to the 2D puzzle game!\n");
    printf("1. New Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");
    printf("Enter your selection: ");
    scanf("%d",&selection);
    switch (selection)
    {
    case 1:
        drawing(flag,c,n,sayac);
        break;
    case 2:
        printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\nDiagonal moves are not allowed. The user will input their desired move using the following keys: 'a' forleft, 'd' for right, 'w' for up, and 's' for down. \nThese moves should be defined at the beginning of the codewith direction names as the keys. \nAny control or selection with [a, d, w, s] characters will result in amissgrading. \nThe game will prompt the user for a new move after each move is made until the game isover.\nThe current state of the room should be printed after each move, except when the character reaches thedoor. \nIf the character attempts to move through a wall, a warning message should be displayed. \nThegame ends when the character reaches the door, and a message should be displayed to notify the userthat the game is over and how many moves were made during the game.");
        break;
    case 3:
        printf("See you later...\n");
        return 0;
        break;
    default:
        printf("invalid selection, please select again: \n");
        game();
        break;
    }
    return 1;
}
