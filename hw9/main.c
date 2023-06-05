#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct boardstruct {
    char type;
    int value;
};

struct snakestruct {
    int x;
    int y;
};

struct boardstruct*** init_board() {
    struct boardstruct*** board = (struct boardstruct***)malloc(10 * sizeof(struct boardstruct**));
    // Allocate memory for each cell and initialize with empty boardstructs
    for (int i = 0; i < 10; i++) {
        board[i] = (struct boardstruct**)malloc(10 * sizeof(struct boardstruct*));
        for (int j = 0; j < 10; j++) {
            board[i][j] = (struct boardstruct*)malloc(sizeof(struct boardstruct));
            board[i][j]->type = 'e';
            board[i][j]->value = 0;
        }
    }
    
    int xbait = 0, ybait = 0;
    int xobs = 0, yobs = 0;

    while (xbait == 0 && ybait == 0) {
        xbait = rand() % 10;
        ybait = rand() % 10;
    }

    while (1) {
        xobs = rand() % 10;
        yobs = rand() % 10;
        if (!(xobs == 0 && yobs == 0) && !(xobs == xbait && yobs == ybait)) {
            break;
        }
    }

    board[xbait][ybait]->type = 'b';
    board[xobs][yobs]->type = 'o';
    board[xobs][yobs]->value = rand() % 9 + 1;

    return board;
}
void draw_board(struct boardstruct*** board, struct snakestruct* snake, int snakeSize) {
    
    system("clear");
    printf("┌--------------------┐\n");
    
    for (int i = 0; i < 10; i++) {
        printf("|");
        for (int j = 0; j < 10; j++) {
            int isSnake = 0;
            for (int k = 0; k < snakeSize; k++) {
                if (snake[k].x == j && snake[k].y == i) {
                    if (k == 0) {
                        printf("o");
                    } else {
                        printf("x");
                    }
                    isSnake = 1;
                    break;
                }
            }
            
            if (!isSnake) {
                if (board[i][j]->type == 'e') {
                    printf(" ");
                } else if (board[i][j]->type == 'b') {
                    printf("･");
                } else if (board[i][j]->type == 'o') {
                    printf("%d", board[i][j]->value);
                }
            }
            
            printf(" ");
        }
        
        printf("|\n");
    }
    
    printf("└--------------------┘\n");
}


void move(struct boardstruct*** board, struct snakestruct* snake, int snakeSize,char *lastDirection) {
    while(1){
        char direction;
        while (1) { // while loop for the iteration of prompting until the user enters a legal move.
            printf("\nEnter your move: ");
            scanf("%c", &direction);
            while (getchar() != '\n');
            if (direction == 'd' || direction == 'a' || direction == 'w' || direction == 's') {
                break;
            } 
            else {
                printf("\nPlease enter a legal move!!!:");
            }
        }
        //printf("last direction: %c\n",*lastDirection);
        ////////////  LAST DIRECTION AYARLA //////////////////////////////////////////////////

        if (direction == 'w') {
                if (*lastDirection != 's' || snakeSize == 2) {
                    snake[0].y -= 1;
                    *lastDirection = direction;
                    break;
                }
                draw_board(board,snake,snakeSize);
        }
        else if (direction == 's') {
            if (*lastDirection != 'w' || snakeSize == 2) {
                snake[0].y += 1;
                *lastDirection = direction;
                break;
            }
            draw_board(board,snake,snakeSize);
        }
        else if (direction == 'a') {
            if (*lastDirection != 'd' || snakeSize == 2) {
                snake[0].x -= 1;
                *lastDirection = direction;
                break;
            }
            draw_board(board,snake,snakeSize);
        }
        else if (direction == 'd') {
            if (*lastDirection != 'a' || snakeSize == 2) {
                snake[0].x += 1;
                *lastDirection = direction;
                break;
            }
            draw_board(board,snake,snakeSize);
        }
        
    }

    


}
int update(struct boardstruct*** board, struct snakestruct** snake, int* snakeSize) {
    static int moveCounter = 0;  // Static variable to keep track of the number of moves

    // Check if the snake ate a bait
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 10; k++) {
            if (board[i][k]->type == 'b') {
                if (((*snake)[0].x == k) && ((*snake)[0].y == i)) {
                    // Increase the snake's length and generate new bait
                    board[i][k]->type = 'e';
                    (*snakeSize)++;
                    (*snake) = (struct snakestruct*)realloc(*snake, (*snakeSize) * sizeof(struct snakestruct));
                    int xbait, ybait;
                    while (1) {
                        xbait = rand() % 10;
                        ybait = rand() % 10;

                        // Check if the new bait doesn't overlap with snake or existing bait
                        int isOverlap = 0;
                        for (int k = 0; k < *snakeSize; k++) {
                            if ((xbait == (*snake)[k].x) && (ybait == (*snake)[k].y)) {
                                isOverlap = 1;
                                break;
                            }
                        }
                        if (!isOverlap) {
                            break;
                        }
                    }
                    board[xbait][ybait]->type = 'b';
                    break;
                }
            }
        }
    }

    // Update the coordinates of the snake's body
    for (int i = *snakeSize - 1; i > 0; i--) {
        (*snake)[i].x = (*snake)[i - 1].x;
        (*snake)[i].y = (*snake)[i - 1].y;
    }

    moveCounter++;  // Increment the move counter

    // Update the obstacles every 5 moves
    if (moveCounter % 5 == 0) {
        int numObstacles = 0;
        for (int i = 0; i < 10; i++) {
            for (int k = 0; k < 10; k++) {
                if (board[i][k]->type == 'o') {
                    numObstacles++;
                }
            }
        }

        // Generate new obstacles if the maximum limit is not reached
        if (numObstacles < 3) {
            while (1) {
                int xobs = rand() % 10;
                int yobs = rand() % 10;

                // Check if the obstacle doesn't overlap with snake or bait
                int isOverlap = 0;
                for (int k = 0; k < *snakeSize; k++) {
                    if (((*snake)[k].x == xobs) && ((*snake)[k].y == yobs)) {
                        isOverlap = 1;
                        break;
                    }
                }
                if (!isOverlap && (board[xobs][yobs]->type != 'b')) {
                    board[xobs][yobs]->type = 'o';
                    board[xobs][yobs]->value = rand() % 9 + 1;
                    break;
                }
            }
        }
    }

    // Check if the bait overlaps with the snake's tail and regenerate if necessary
    if (board[(*snake)[0].y][(*snake)[0].x]->type == 'b') {
        int isOverlap = 0;
        for (int k = 1; k < *snakeSize; k++) {
            if (((*snake)[k].x == (*snake)[0].x) && ((*snake)[k].y == (*snake)[0].y)) {
                isOverlap = 1;
                break;
            }
        }
        if (isOverlap) {
            // Generate new bait
            int xbait, ybait;
            while (1) {
                xbait = rand() % 10;
                ybait = rand() % 10;

                // Check if the new bait doesn't overlap with snake or existing bait
                int isOverlap = 0;
                for (int k = 0; k < *snakeSize; k++) {
                    if ((xbait == (*snake)[k].x) && (ybait == (*snake)[k].y)) {
                        isOverlap = 1;
                        break;
                    }
                }
                if (!isOverlap) {
                    break;
                }
            }
            board[(*snake)[0].y][(*snake)[0].x]->type = 'e';
            board[xbait][ybait]->type = 'b';
        }
    }

    return 1;
}



int check_status(struct boardstruct*** board, struct snakestruct* snake, int snakeSize) {
    if (snake[0].x < 0 || snake[0].y < 0 || snake[0].x > 9 || snake[0].y > 9) {
        return 1;
    }
    for(int i = 0;i < 10;i++){
        for(int k = 0;k < 10;k++){
            if(board[i][k]->type == 'o'){
                if((snake[0].x == k) && (snake[0].y == i)){
                    if(board[i][k]->value > snakeSize - 1){
                        return 1;
                    }
                    else{
                        board[i][k]->type = 'e';
                    }

                }
            }
        }
    }
    for(int k = 1; k < snakeSize - 1;k++){
        if((snake[0].x == snake[k].x) && (snake[0].y == snake[k].y)){
            return 1;
        }
    }
    return 0;
}
void play(struct boardstruct*** board) {
    int snakeSize = 2;
    struct snakestruct* snake = (struct snakestruct*)malloc(sizeof(struct snakestruct));
    snake[0].x = 0;
    snake[0].y = 0;
    char lastDirection = ' ';
    while (1) {
        draw_board(board, snake, snakeSize);
        //printf("\nsnake size is: %d\n", snakeSize - 1);
        move(board, snake, snakeSize,&lastDirection);
        if (check_status(board, snake, snakeSize)) {
            printf("Game Over! You lost.\n");
            break;
        }
        update(board, &snake, &snakeSize);
    }
    free(snake);
}


int main() {
    srand(time(NULL));
    // Initialize the board
    struct boardstruct*** board = init_board();

    play(board);

    // Free the dynamically allocated memory for the board
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);



    return 0;
}
