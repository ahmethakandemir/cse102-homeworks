#include <stdio.h>
#include <math.h>

int main(){
	printf("Welcome to part2!!\n\n");
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

	typedef enum colors{
		RED,
		GREEN,
		BLUE,
		YELLOW,
		ORANGE

	}color;
	
	float painter[5][3] = {
		{1,0,0},		//RED		//0
		{0,1,0},		//GREEN		//1
		{0,0,1}, 		//BLUE		//2
		{0.5,0.5,0}, 	//YELLOW	//3
		{0.5,0.4,0.2}	//ORANGE	//4
	};
	
	int index;
	float closest = 99,distance;

	float mixed[3] = {(painter[first][0]+painter[second][0]) / 2,(painter[first][1]+painter[second][1]) / 2,(painter[first][2]+painter[second][2]) / 2};
	
	for(int i = 0;i < 5;i++){
		distance = sqrt(pow(painter[i][0] - mixed[0],2) + pow(painter[i][1]- mixed[1],2) + pow(painter[i][2] - mixed[2],2));
		if (distance < closest){
			closest = distance;
			index = i;
		}
	}
	printf("Mixed color: ");
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
		printf("%.1f",mixed[i]);
		if(i < 2){
			printf(", ");
		}
	}
	printf("] ");

	printf("\n");
	return 0;
}