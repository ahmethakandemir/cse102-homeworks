#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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


void move(struct boardstruct*** board, struct snakestruct* snake, int snakeSize) {
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

    switch (direction) {
        case 'w':
            snake[0].y -= 1;
            break;
        case 's':
            snake[0].y += 1;
            break;
        case 'a':
            snake[0].x -= 1;
            break;
        case 'd':
            snake[0].x += 1;
            break;
        default:
            break;
    }
}

int update(struct boardstruct*** board, struct snakestruct* snake, int* snakeSize) {
    static int moveCounter = 0;  // Static variable to keep track of the number of moves

    // Check if the snake ate a bait
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 10; k++) {
            if (board[i][k]->type == 'b') {
                if ((snake[0].x == k) && (snake[0].y == i)) {
                    // Increase the snake's length and generate new bait
                    board[i][k]->type = 'e';
                    (*snakeSize)++;
                    int xbait, ybait;
                    while (1) {
                        xbait = rand() % 10;
                        ybait = rand() % 10;
                        // Check if the new bait doesn't overlap with snake or existing bait
                        if (!(board[xbait][ybait]->type == 'b') && !(board[xbait][ybait]->type == 'o')) {
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
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
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
            int xobs, yobs;
            while (1) {
                xobs = rand() % 10;
                yobs = rand() % 10;
                // Check if the obstacle doesn't overlap with snake or bait
                if (!(board[xobs][yobs]->type == 'b') && !(board[xobs][yobs]->type == 'o')) {
                    break;
                }
            }
            board[xobs][yobs]->type = 'o';
            board[xobs][yobs]->value = rand() % 9 + 1;
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
                    if(board[i][k]->value > snakeSize){
                        return 1;
                    }
                    else{
                        board[i][k]->type = 'e';
                    }

                }
            }
        }
    }
    return 0;
}

void play(struct boardstruct*** board) {
    int snakeSize = 2;
    struct snakestruct* snake = (struct snakestruct*)malloc(snakeSize * sizeof(struct snakestruct));
    snake[0].x = 0;
    snake[0].y = 0;

    while (1) {
        draw_board(board, snake, snakeSize);
        printf("\nsnake size is: %d\n",snakeSize);
        move(board, snake, snakeSize);
        if (check_status(board,snake, snakeSize)) {
            printf("Game Over! You lost.\n");
            break;
        }
        update(board,snake,&snakeSize);
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
