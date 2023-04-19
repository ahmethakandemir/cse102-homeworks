#include <stdio.h>
#include <math.h>

int main(){

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
	int first,second;
	int distance;
	printf("Enter the colors: ");
	scanf("%d %d",&first,&second);
	float mixed[3] = {(painter[first][0]+painter[second][0]) / 2,(painter[first][1]+painter[second][1]) / 2,(painter[first][2]+painter[second][2]) / 2};
	float closest = 0;
	for(int i = 0;i < 5;i++){
		float closest = 1;
		for(int k = 0;k < 3;k++){
			distance = sqrt((painter[i][k]) * (painter[i][k]) + (mixed[k] * mixed[k]));
			if(distance < closest){
				closest = distance;
			}
		}
		
	}



	return 0;
}