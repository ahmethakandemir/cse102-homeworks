#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// defined keys of movement
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

int n = 1; // n is used to calculate the size.
int d = 0; // d is coordinate of Door.
int c = 0; // c is coordinate of Character we move.
int welcome = 0; // this is a checking value to print welcome when the user entered the game, and not printing again.
// I needed to declare global parameters beacuse if I didn't, I would have need to add hundreds of parameters to functions as if there isn't already.

int drawing(int flag,int c,int n,int sayac);
void gameplay(int c,int n,int sayac);
int status(int c,int d);
int game(int welcome);

int main(){
    system("clear"); // I used this function often to make my game more aesthetic.
    game(0);         // starting the game by going into main menu.

}

int game(int welcome){ 
    char selection; // selection in main menu. 
    if (welcome == 0){ // saying welcome to user at the first entrance.
        printf("Welcome to the 2D puzzle game!, Have Fun!!!!!\n");
    }
    else if(welcome == 1){ // saying welcome again at second entrance.
        printf("\n\nWelcome again......\n");
    }
    printf("\n1. New Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");
    printf("Enter your selection: ");
    scanf(" %c",&selection);
    switch (selection) // selecting the option.
    {
    case '1':          // if 1 is selected, screen will be cleared and game will be on.
        system("clear");
        drawing(0,c,n,0); // game will be started with flag = 0 and sayac = 0 parameters.
        game(1);
        break;
    case '2':          // if 2 is selected, screen will be cleared and help message will be printed.
        system("clear");
        printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\nDiagonal moves are not allowed. The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down.\nThe game will prompt the user for a new move after each move is made until the game is over. \nThe game ends when the character reaches the door.\n");
        game(1);
        break;
    case '3':          // if 3 is selected, program will print see you message and terminate itself.
        printf("See you later...\n");
        return 0;
        break;
    default:           // if anything else is entered, screen will be cleared and reprompting the user again.
        system("clear");
        printf("invalid selection... \n\n");
        game(1);
        break;
    }
    return 1;
}

int drawing(int flag,int c,int n,int sayac){    // drawing the room function

    if(flag == 0){  // flag is again used to find out if the function run for the first time, because at second time user not be asked for board size.
        srand(time(NULL));  // this function is for creating random coordinates at every run of the program
        printf("Enter board size: ");
        scanf("%d",&n); // taking the size input.
        c = 0;      // c is coordinate of Character we move.
        d = 0;      // d is coordinate of Door.
        while((n < 5) || (n > 10)){ // if the board is smaller than 5x5 or bigger than 10x10 as in rules, user will be reasked again and again until enters a valid value for size.
            printf("'n' can't be less than 5, and more than 10. Enter n value again: ");
            scanf("%d",&n);
            
        }
        while(c == d){              // generating random coordinates and assigning them into a variable.
            d = rand()%(n*n);
            c = rand()%(n*n);

        }
        system("clear");            // clearing the screen to start the game.
        printf("\n");
    }
// coordinating system is basically giving nums to every cell, if the size is 5x5 and first cells coordinate is 0, second line's first cell's coordinate will be 5, and third line's first cell's coordinate will be 10.
    int counter = 0;                // counter is being the coordinate of every printed cell, when it equals to C or D, prints C or D in the correct coordinate.

    if(status(c,d)){                // with this function, program checks if C and D is at the same position, and if it is, returns.
        printf("~*~*~*~*~*~*~*~*~*~*~*~\n\nYOU WON!!(in %d moves!!)\n\n~*~*~*~*~*~*~*~*~*~*~*~\n",sayac); 
        return 1;
    }

    // here is printing the room.
    for(int i = 0; i < (2*n)+1; i++){  // first, printing the ceiling.
        printf("-");
    }

    for(int i = 0; i < n;i++){          // printing '| ' to create every cell, if cell's coordinate is equal to C or D letters coordinate, prints '|C' or '|D' instead of '| '.
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
            counter++;                  // increasing counter value at every printing operation, to go to next coordinate.
            
        }
        printf("|");                    // printing '|' after every line to close last cell's right side.
    }
    printf("\n");
    for(int i = 0; i < (2*n)+1; i++){
        printf("-");                    // and lastly, printing the floor.
    }
    
    printf("\n");
    flag = 1;                           // flag = 1 because we don't want to asked for size, or another random places for C and D.
    
    gameplay(c,n,sayac);                // calling the gameplay function to make some movement, because C and D is not in the same location, that means we still need to make some moves.

    return 1;
}



void gameplay(int c,int n,int sayac){   // this is the function where we make moves.
    char input;
    
    printf("enter your move: ");
    scanf(" %c",&input);                // program is taking the movement key.
        
    while ( getchar() != '\n' ){} // this part is used for taking only first letter of movement input.
    // it is clearly a blank while loop, because I only wanted to take the first letter of movement input in case the player gives more than one letter as input.
    // for example if the player enters wawaasd, the scanf will take the 'w' at the beginning, and getchar will clear the rest to avoid taking more than one input.
    
    system("clear");              // clearing the screen to avoid mess in the game interface.
    switch (input)                // making the move.
    {
    case UP:
        if(c >= n){               // checking whether Character's coordinate is already on the 'top line' or not.
            c = c - n;            // if it is not, coordinate will be decreased by one line, so Character will be in one cell up.
            printf("\n");
        }
        else{                     // if it is, user will be warned by a message because Character can't go more upwards.
            printf("you hit the wall,try again!!\n");// warning message when hit the wall.
        }
        break;
    case DOWN:
        if (c + n < n * n){       // checking whether Character's coordinate is already on the 'bottom line' or not.
            c = c + n;            // if it is not, coordinate will be increased by one line, so Character will be in one cell down.
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    case LEFT:                   
        if (c % n > 0){           // checking whether Character's coordinate is already on the 'leftmost' cell or not.
            c = c - 1;            // if it is not, coordinate will be decreased by one, so Character will be in one cell left.
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    case RIGHT:                     
        if (c % n < n - 1){       // checking whether Character's coordinate is already on the 'rightmost' cell or not.
            c = c + 1;            // if it is not, coordinate will be increased by one, so Character will be in one cell right.
            printf("\n");
        }
        else{
            printf("you hit the wall,try again!!\n");
        }
        break;
    default:                      // if user did not press any of the valid keys, will be warned, nothing will be changed and board will be drawed again, and the user need to make a valid move.
        printf("invalid movement key pressed, try again!!\n");
        sayac--;                  // move counter will be decreasing by one because the user did not pressed a valid key.
        break;
    }
    sayac++;
    drawing(1,c,n,sayac);         // going back to drawing the board function to draw the board again and make the move again until status function returns 1 value.
    // flag parameter is 1 to not ask for the size again, and the new coordinate of Character is sended to drawing function to print it in it's new location.
}

int status(int c,int d){          // this is where the program checks whether Door's coordinate and Character's coordinate is equaled or not.
    if(c == d){                   // if equals, returns 1 and ends the game, in line 86.
        return 1;
    }
    return 0;                     // if not, returns 0 and game will continue.
}

