#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_WORD_SIZE 13
#define maxoccurance 300000
const char dictionary[20] = {"dictionary.txt"};
const char inputtext[20] = {"input.txt"};
const char ignoretext[20] = {"ignore.txt"};
char temp[300000][MAX_WORD_SIZE];

int findwordnumdictionary(const char * file_name){
	FILE *fpdict;
	fpdict=fopen(file_name,"r");
	int c;
	int wordnumd;
	while(1){
		c=fgetc(fpdict);
		if(c==61){
			fscanf(fpdict, "%d", &wordnumd);		
			break;
		}
	}
	fclose(fpdict);
	return wordnumd;
}

int findvectorsizedictionary(const char * file_name){
	FILE *fpdict;
	fpdict=fopen(file_name,"r");
	int c;
	int vecsize, count=0;
	while(1){
		c=fgetc(fpdict);
		if(c==61){
			count++;
		}
		if(count==2){
			fscanf(fpdict, "%d", &vecsize);
			break;
		}
	}
	fclose(fpdict);
	return vecsize;
}
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
	int x,y,i,j=0,c=0;
	char line[100], temp;
	x=findwordnumdictionary(dictionary);
	y=findvectorsizedictionary(dictionary);
	FILE *fpdict;
	float vecs[x][y];
	fpdict=fopen(file_name,"r");
	fgets(line, 100, fpdict);
	for(i=0; i<x; i++){
		fscanf(fpdict,"%s", dict[i]);
		for(j=0; j<y; j++){
			fscanf(fpdict, "%f", &vecs[i][j]);
		}	
	}
	dict[x][0] = '-';
	dict[x][1] = '\0';
	
	//testing vecs
	/*for(i=0; i<x; i++){
		for(j=0; j<y; j++){
			printf("%f ", vecs[i][j]); 
		}
		printf("\n");
	}*/
	return x;	
}
void fillvectors(const char * file_name, double vecs[findwordnumdictionary(dictionary)][findvectorsizedictionary(dictionary)]){
	int x,y,i,j=0,c=0;
	char line[100], temp;
	x=findwordnumdictionary(dictionary)+1;
	y=findvectorsizedictionary(dictionary);
	char dict[x][MAX_WORD_SIZE];
	FILE *fpdict;
	fpdict=fopen(file_name,"r");
	fgets(line, 100, fpdict);
	for(i=0; i<x; i++){
		fscanf(fpdict,"%s", dict[i]);
		for(j=0; j<y; j++){
			fscanf(fpdict, "%lf", &vecs[i][j]);
		}	
	}
	i++;
	vecs[i][0]='-';
}
void printarray(char dict[][MAX_WORD_SIZE], int size){
	for (int i = 0; i <= size; i++) {
        printf("%s ", dict[i]); 
        //printf("\n");
    }
}
int read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]){

    FILE *fpignore;
    FILE *fptext;
	FILE *fptemp;
	
    char ignore[300][MAX_WORD_SIZE];
    
    fpignore = fopen(ignore_file, "r");
    int lines=0,c=0;
    while(1){
        c=fgetc(fpignore);
        if(c==EOF)break;
        if(c==10)lines++;
    }
    fclose(fpignore);
    printf("\n%d", lines);
    fpignore = fopen(ignore_file, "r");
    int i,k;
    for(i=0; i<lines; i++){
        fscanf(fpignore,"%s", ignore[i]);
    }
    fclose(fpignore);
    printarray(ignore, lines);
	fptext = fopen(text_file,"r");
	fptemp = fopen("temp.txt","w+");
	while(1){
		c=getc(fptext);
		if(c==EOF)break;
		if(!(c>=0 && c<=127)){
			putc(' ', fptemp);
		}
		if(c=='\''|| c=='-'){ // 39 45 95 96
			c=getc(fptext);
		}
		else if((c>32 && c<39)||(c>39 && c<48 && c!=45)||(c>57 && c<65)||(c>90 && c<97)||(c>122 && c<127)||c<0){
			c=getc(fptext);
			//if(c==46)continue;
			putc(' ', fptemp);
			//c=getc(fptext);
		}
		if((c<58 && c>47)||(c>65 && c<91) || (c>96 && c<123) || c==' '|| c==10){
			if((c>58 || c<47)&&(c<65 || c>91)&&(c<96 || c>123) && c!=' '&& c!=10) putc(' ',fptemp);
			else putc(c, fptemp);
		}	
	}
	fclose(fptext);
	fclose(fptemp);
     
    fptemp=fopen("temp.txt", "r");
    i=0, k=0;
    int j, flag;
    while(1){
        flag=0;
        fscanf(fptemp,"%s",temp[i]);
        if(temp[i][0]=='\0')break;
        for(j=0; j<lines; j++){
            if((strcmp(temp[i], ignore[j]))==0)flag=1;
        }
        //printf("%s",temp[0]);
        if(flag==0){
            for(j=0; temp[i][j]!='\0'; j++){
            	//printf(" k %d i %d ", k,i);
            	words[k][j]=temp[i][j];
            }
            k++;
        }
        i++;
    }
    words[k][0]='-';
    fclose(fptemp);
   // printarray(words,k);
    return k-1;
}

double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, double vecs[][findvectorsizedictionary(dictionary)]){
	//first find the index of w1, then find the closest
	int i, j, firstwindex,x,y,flag=0, answer;
	x=findwordnumdictionary(dictionary);
	y=findvectorsizedictionary(dictionary);
	for(i=0; i<x; i++){
		if((strcmp(w1, dict[i]))==0){
			firstwindex=i;
			flag=1;
		}	
	}	
	if(flag==0){
		//printf("\n there is no such word in dictionary ");
		return 0;
	}
	//printf("\n%d", firstwindex);
	double mindistance=40, distance=0, temp;
	//threshold=5;
	for(i=0; i<x; i++){
		distance=0;
		for(j=0; j<y; j++){
			distance+=(vecs[firstwindex][j]-vecs[i][j])*(vecs[firstwindex][j]-vecs[i][j]);
		
		}
		distance=sqrt(distance);
		//printf("\n%d distance with %s %lf", i, dict[i], distance);
		if(distance<mindistance && distance!=0){
			mindistance=distance;
			for(j=0; dict[i][j]!='\0'; j++){
				w2[j]=dict[i][j];
			}
			w2[j]='\0';
		}	
	}
	if(threshold<mindistance)return -1; 
	printf("\n the closest word to %s is %s, their distance is %lf", w1, w2,mindistance);
	return mindistance;
}

int findoccur(char dict[][MAX_WORD_SIZE], double vecs[][findvectorsizedictionary(dictionary)], char *w1){
	int occurance=0,i,x;
	x=findwordnumdictionary(dictionary);
	for(i=0; i<x; i++){
		if((strcmp(w1, dict[i]))==0)occurance++;
	}	
	return occurance;
}

int main(){
	int x,y,z;
	x=findwordnumdictionary(dictionary)+1;
	y=findvectorsizedictionary(dictionary);
	//printf("%d %d", x, y);
	char dict[x][MAX_WORD_SIZE];
	char words[300000][MAX_WORD_SIZE];
	char w1[13]={"lightly"};
	char w2[13];
	double vecs[x][y];
	read_dict(dictionary, dict);
	//printf("\n %s \n", dict[999]);
	//printf("\n%s", dict[x]);
	//printarray(dict, x);
	read_text(inputtext,ignoretext,words);
	//printarray(words, 16000);
	//printf(" %d",z);  //num of words read
	//fillvectors(dictionary,vecs);
	//checking for vectors
	/*int i,j;
	for(i=0; i<x; i++){
		printf("\n Vecs %d: \n", i);
		for(j=0; j<y; j++){
			printf("%f ", vecs[i][j]); 
		}
		printf("\n");
	}*/
	//dissimilarity(w1,w2,dict,6, vecs);
	//int occur[100][maxoccurance];
	int o;
	//o=findoccur(dict,vecs,w1);
	//printf("\n%d ", o);
}
