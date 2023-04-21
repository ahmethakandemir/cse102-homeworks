#include <stdio.h>
#include <math.h>
// declaring functions.
int part1();
int lowercase(int);

int part2();

int part3();
int drawingBoard(int,int,char);
int check();
int again();
void reset();
int player = 2;         // determining player, initialized as 2 because we are getting it's module with 2.
int board[3][3] = {0};  // declaring board.

int main(){
    part1();
    part2();
    part3();
}

int part1(){
    printf("Welcome to part1!!\n\n");
    FILE* myfile;
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int counts[26] = {0};
    char input[30];
    printf("Input file name: ");
    scanf("%s",input);      // getting file's name.
    myfile = fopen(input,"r");  //  opening file if exists.

    if(myfile == NULL){
        perror("Error opening file"); // giving error if file is not found.
        return 0;
    }
    
    printf("Letter frequency: \n");
    while(1){
        int c = fgetc(myfile);  // getting characters one by one.
        if(c == EOF){           // if eof, break.
            break;
        }
        for(int i = 0;i < 26; i++){
            if(c == letters[i]){
                counts[i]++;    // incrementing the count array simultaneously.
            }
            if(c <= 90 && c >= 65){ // if letter is uppercase, lowercase function is called.
                if(lowercase(c) == letters[i]){
                    counts[i]++;
                }
            }
        }
    }

    for(int i = 0;i < 26; i++){ // displays counts of letters.
        printf("%c : %d\n",letters[i] - 32,counts[i]);
    }
    return 0;
}
int lowercase(int c){   // uppercase =>> lowercase
    return (c += 32);
}
// starting of part 2.

typedef enum colors{    //declaring colors as numbers.
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE

}color;

color mix(color first,color second);
color colorMixer(color first,color second, color (*mix)(color first,color second)); // function with a function pointer 

float painter[5][3] = {
	{1,0,0},		//RED		//0
    {0,1,0},		//GREEN		//1
    {0,0,1}, 		//BLUE		//2
    {0.5,0.5,0}, 	//YELLOW	//3
    {0.5,0.4,0.2}	//ORANGE	//4
};

int part2(){

    color(*mixp)(color first,color second) = &mix; // declaring function pointer.

	printf("\n\nWelcome to part2!!\n\n");
    // getting inputs......
	int first = 10,second = 10;
	char s1,s2;
	while(1){
		printf("Enter color 1(r,g,b,y,o): ");
		scanf(" %c",&s1);
		switch (s1)
		{
		case 'r':
		case 'R':
			first = 0;
			break;
		case 'g':
		case 'G':
			first = 1;
			break;
		case 'b':
		case 'B':
			first = 2;
			break;
		case 'y':
		case 'Y':
			first = 3;
			break;
		case 'o':
		case 'O':
			first = 4;
			break;
		default:
			printf("\nwrong selection!!\n");
		}
		if(first < 5){
			break;
		}
	}
		while(1){
		printf("Enter color 2(r,g,b,y,o): ");
		scanf(" %c",&s2);
		switch (s2)
		{
		case 'r':
		case 'R':
			second = 0;
			break;
		case 'g':
		case 'G':
			second = 1;
			break;
		case 'b':
		case 'B':
			second = 2;
			break;
		case 'y':
		case 'Y':
			second = 3;
			break;
		case 'o':
		case 'O':
			second = 4;
			break;
		default:
			printf("\nwrong selection!!\n");
		}
		if(second < 5){
			break;
		}
	}
    color index;
    index = colorMixer(first,second,mixp); // calling the mixing function.
    // printing the output
	switch (index)
	{
	case 0: printf("RED");break;
	case 1: printf("GREEN");break;
	case 2: printf("BLUE");break;
	case 3: printf("YELLOW");break;
	case 4: printf("ORANGE");break;
	default:
		printf("\nError!!\n");
		break;
	}
	printf(" [");
	for(int i = 0; i < 3; i++){
		printf("%.1f",painter[index][i]);
		if(i < 2){
			printf(", ");
		}
	}
	printf("] ");

	printf("\n");

	return 0;
}
color colorMixer(color first,color second, color (*mix)(color first,color second)){
    return mix(first,second);
}

color mix(color first, color second){ // this function mixes two given colors using euclidian distance algorithm.
	int index;
	float closest = 99,distance;

	float mixed[3] = {(painter[first][0]+painter[second][0]) / 2,(painter[first][1]+painter[second][1]) / 2,(painter[first][2]+painter[second][2]) / 2};
	
	for(int i = 0;i < 5;i++){ // finding minimum distance.
		distance = sqrt(pow(painter[i][0] - mixed[0],2) + pow(painter[i][1]- mixed[1],2) + pow(painter[i][2] - mixed[2],2));
		if (distance < closest){
			closest = distance;
			index = i;
		}
	}
	printf("Mixed color: ");
    return index;
}

int part3(){
    printf("\n\nWelcome to part3!!\n\n");
    char move;
    int x,y;
    drawingBoard(0,0,0); // initialized with empty board
    while(1)    // iterates until the game finishes.
    {
        if(player % 2 == 1){
            move = 'o';
        }
        else{
            move = 'x';
        }

        printf("Player %d's Turn(%c): ", player % 2 + 1,move);
        while(1){   //taking inputs until valid numbers entered.
            scanf("%d %d",&x,&y);
            if((x >= 0 && x <= 2) && (y >= 0 && y <= 2)){
                break;
            }
            printf("please enter valid numbers!!: \n");
            getchar();
        }

        drawingBoard(x,y,move); // drawing the board.
        player++;   // switching player.

        if(check()){    //checking if the game finished or not.
            if(!again()){   // if user wants to play again, loop continues, else returns.
                return 0;
            }
        }
    }

    return 0;
}


int drawingBoard(int i,int k,char type){ // drawing board.
    printf("\n");
    if(board[i][k] == 0){   // if the cell is not filled, fills with type.
        board[i][k] = type; 
    }
    else{
        printf("entered wrong location!\n"); 
        getchar();
        player--;
    }
    
    for(int i = 0; i < 3; i++){
        for(int k = 0; k < 3; k++){
            if(board[i][k] == 0){ // if the cell empty, print '_'.
                printf("_ ");
            }
            else{                  // else print the type(x or o)
                printf("%c ",board[i][k]);
            }
        }
        printf("\n");
    }

    printf("\n");
    return 1;
}

int again(){    // check if they want to play again or not.
    char secim;
    reset();
    printf("\ndo you want to play again??: ");
    if(scanf(" %c",&secim) == 1){
        switch (secim)
        {
        case 'y':case 'Y':
            reset();
            player = 2;
            drawingBoard(0,0,0);
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

int check(){    // checking the game ended or not
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
    // if there is no winner, that means the game ended with tie situation.
    printf("\nit is tie!\n");
    return 1;
}
void reset(){   // reseting the board to all 0's.
    for(int i = 0; i < 3; i++){
        for(int k = 0; k < 3; k++){
            board[i][k] = 0;
        }
    }
}



