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
    srand(time(NULL));
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

int draw_board(struct boardstruct*** board, struct snakestruct* snake, int snakeSize) {
    // Draw the horizontal edges
    system("clear");
    printf("┌--------------------┐\n");
    // Iterate over each row and column to draw the board

    for (int i = 0; i < 10; i++) {
        printf("|");
        for (int j = 0; j < 10; j++) {
            int isSnake = 0;
            for (int k = 0; k < snakeSize; k++) {
                if (snake[k].x == j && snake[k].y == i) {
                    printf("o");
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
    // Draw the horizontal edges
    printf("└--------------------┘\n");

    return 0;
}

void move(struct boardstruct*** board, struct snakestruct* snake, int snakeSize) {
    char direction;
    while (1) { // while loop for the iteration of prompting until the user enters a legal move.
        printf("\nEnter your move: ");
        scanf("%c", &direction);
        while (getchar() != '\n')
            ;
        //printf("%d-%c",movement,direction);
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

int check_status(struct snakestruct* snake, struct boardstruct*** board, int snakeSize) {
    if (snake[0].x < 0 || snake[0].y < 0 || snake[0].x > 9 || snake[0].y > 9) {
        return 1;
    }
    return 0;
}

void play(struct boardstruct*** board) {
    int snakeSize = 1;
    struct snakestruct* snake = (struct snakestruct*)malloc(snakeSize * sizeof(struct snakestruct));
    snake[0].x = 0;
    snake[0].y = 0;

    while (1) {
        draw_board(board, snake, snakeSize);
        move(board, snake, snakeSize);
        if (check_status(snake, board, snakeSize)) {
            printf("Game Over! You lost.\n");
            break;
        }
        //update(board);
    }
}

int main() {
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
