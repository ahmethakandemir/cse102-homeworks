#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

const char dictionary[20] = "dictionary.txt";
const char inputtxt[20] = "input.txt";
const char ignoretxt[20] = "ignore.txt";

#define MAX_WORD_SIZE 13 // one more byte for eof char.
#define MAX_WORD_COUNT 100


int numwords(){
    FILE * dict;
    dict = fopen("dictionary.txt","r");
    int c,numword;
    while(c != 61){
        c = fgetc(dict);
    }
    fscanf(dict,"%d",&numword);
    fclose(dict);
    return numword;
}
int vectorsize(){
    FILE * dict;
    dict = fopen("dictionary.txt","r");
    int c,vector;
    while(c != 61){
        c = fgetc(dict);
    }
    c = fgetc(dict);
    while(c != 61){
        c = fgetc(dict);
    }
    fscanf(dict,"%d",&vector);
    fclose(dict);
    return vector;
}



void vectorAdding(const char *  file_name, char dict[][MAX_WORD_SIZE],float vecs[numwords()][vectorsize()]){

	int i,j=0,c=0,numss,vectorss;
    char line[100];
	FILE *fpdict;
    fpdict = fopen("dictionary.txt","r");
    numss = numwords();
    fclose(fpdict);
    vectorss = vectorsize();
	fpdict=fopen(file_name,"r");
	/*while (c != 10){
        c = fgetc(fpdict);
        //printf("%c",c);
    }*/
    fgets(line,100,fpdict);
	for(i=0; i< numss; i++){
		fscanf(fpdict,"%s", dict[i]);
		for(j=0; j<vectorss; j++){
			fscanf(fpdict, "%f", &vecs[i][j]);
		}	
	}

	dict[numss][0] = '-';
	dict[numss][1] = '\0';/*
    for(i=0; i<numss; i++){
		for(j=0; j<vectorss; j++){
			//printf("%.5f ", vecs[i][j]);
		}
		printf("\n");
	}
    for(i = 0;i < numwords(); i++){
        printf("%s ",dict[i]);
    }*/
	
}


double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, float vecs[numwords()][vectorsize()]){

    int i,tempint;
    for(i = 0; i < numwords();i++){
        if(strcmp(w1,dict[i]) == 0){
            break;
        }
    }
    double temp = 100,sum = 0;
    for(int k = 0;k < numwords();k++){
        sum = 0;
        for(int j = 0;j < vectorsize();j++){
            sum += pow(vecs[k][j] - vecs[i][j],2);
        }
        sum = sqrt(sum);
        if((sum < temp)&&(sum != 0)){
            temp = sum;
            tempint = k;
            //printf("%lf\n",temp);
        }
        if(threshold < temp){
            return -1;
        }
    }
    for(int m = 0;m < MAX_WORD_SIZE; m++){
        w2[m] = dict[tempint][m];
    }

    return temp;
}

int read_dict(const char *  file_name, char dict[][MAX_WORD_SIZE]){
	int i,j=0,c=0,numss,vectorss;
	FILE *fpdict;
    fpdict = fopen("dictionary.txt","r");
    numss = numwords();
    fclose(fpdict);
    vectorss = vectorsize();
	float vecs[numss][vectorss];
	fpdict=fopen(file_name,"r");
	while (c != 10){
        c = fgetc(fpdict);
        //printf("%c",c);
    }
	for(i=0; i< numss; i++){
		fscanf(fpdict,"%s", dict[i]);
		for(j=0; j<vectorss; j++){
			fscanf(fpdict, "%f", &vecs[i][j]);
		}	
	}

	dict[numss][0] = '-';
	dict[numss][1] = '\0';
	
	//testing vecs
	for(i=0; i<numss; i++){
		for(j=0; j<vectorss; j++){
			//printf("%.1f ", vecs[i][j]);
		}
		//printf("\n");
	}
    for(i = 0;i < numwords(); i++){
        //printf("%s ",dict[i]);
    }

	return numss;	
}

int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]){
    FILE * fpinput;
    FILE * fpignore;
    
    char ignore[100][MAX_WORD_SIZE];
    fpignore = fopen(ignore_file,"r");
    int c,counter = 0;
    while(1){
        c = fgetc(fpignore);
        if(c == 10){
            counter++;
        }
        if (c == EOF){
            counter++;
            break;
        }
    }
    int i = 0;
    fclose(fpignore);
    fpignore = fopen(ignore_file,"r");
    while(i < counter){
        fscanf(fpignore,"%s",ignore[i]);
        i++;
    }
    fclose(fpignore);
    
    i = 0;
    int k;
    fpinput = fopen(text_file,"r");
    while(1){
        
        fscanf(fpinput,"%s",words[i]);
        c = fgetc(fpinput);
        if(c == -1){
            break;
        }
        while(((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))){
            c = fgetc(fpinput);
        }
        ungetc(c,fpinput);
        if(!((words[i][0] >= 65 && words[i][0] <= 90) || (words[i][0] >= 97 && words[i][0] <= 122) || (words[i][0] >= 48 && words[i][0] <= 57))){
                for(int m = 0; m < MAX_WORD_SIZE + 1; m++){
                    words[i][m] = words[i][m+1];
                }
                for(k = 1;k < MAX_WORD_SIZE;k++){
                    if(!((words[i][k] >= 65 && words[i][k] <= 90) || (words[i][k] >= 97 && words[i][k] <= 122) || (words[i][k] >= 48 && words[i][k] <= 57))){
                        words[i][k] = '\0';
                    }
                }
            }
        else{
            for(k = 0;k < MAX_WORD_SIZE;k++){
                if(words[i][k] == 39){
                    for(int m = k; m < MAX_WORD_SIZE + 1; m++){
                        words[i][m] = words[i][m+1];
                    }
                }
                if(!((words[i][k] >= 0) && (words[i][k] <= 127))){
                    //words[i][k] = ' ';
                    i++;
                    int e,index;
                    for(e = k,index = 0;e < MAX_WORD_SIZE + 1;e++,index++){
                        //printf("i is : %d\n",i);
                        //printf("char is :%c\n",words[i - 1][e + 3]);
                        words[i][index] = words[i - 1][e + 3];
                        
                    }
                    words[i-2][e+3]= '\0';
                        //printf("1. index is : %s\n",words[1]);
                }
                if(!((words[i][k] >= 65 && words[i][k] <= 90) || (words[i][k] >= 97 && words[i][k] <= 122) || (words[i][k] >= 48 && words[i][k] <= 57))){
                    words[i][k] = '\0';
                    break;
                }
            }
        }
        //printf("%s ",words[i]);
        i++;
    }
    fclose(fpinput);
    //printf("%d",i);

    


    for(int l = 0; l < i+2;l++){
        for(int b = 0;b < counter;b++){
            if(strcmp(ignore[b],words[l]) == 0){
                for(int t = l; t < i;t++){
                    for(int n = 0;n < MAX_WORD_SIZE;n++){
                        words[t][n] = words[t + 1][n];
                    }
                }
            } 
        }
    }

    for(int l = 0; l < i+2;l++){
        //printf("%s ",words[l]);
    }

    //printf("\n\n%s\n",words[6]);
    //printf("word is : %s\n",words[2]);
    return i;
}

void occurence(char inputt[100][MAX_WORD_SIZE],char words[300000][MAX_WORD_SIZE],int enternum,int counter[100]){
    

    int i,j;
    int wordsize = read_text(inputtxt,ignoretxt,words);
    for(i = 0; i < wordsize; i++){
        for(j = 0;j < enternum; j++){
            if(strcmp(inputt[j],words[i]) == 0){
            counter[j]++;
            }
        }   
    }
    //printf("%d",count);
    return;
}
int histogram(const char inputt[][MAX_WORD_SIZE],int enternum, const int occurrences[], const char hist[][MAX_WORD_SIZE+5+20]){

    //     for(int i = 0;i < enternum;i++){
    //     if(occurrences[i] != 0){
    //         printf("occurence of %s is : %d\n",inputt[i],occurrences[i]);
    //     }
    //     else{

    //         printf("%s is not in the input.txt\n",inputt[i]);
    //     }
    // }
    int max = 0;
    int scale;
    
    for(int k = 0;k < enternum;k++){
        if(occurrences[k] > max){
            max = occurrences[k];
        }
    }
    if(max%20!=0){
        scale = max/20 +1;
    }
    else {
        scale = 1;
    }
    int k;
    printf("Enter word(s): ");
    for(int i = 0;i< enternum;i++){

        
        printf("%s ",inputt[i]);
    }
    
    printf("\nScale: %d \n",scale);

    for(int i = 0;i< enternum;i++){
        printf("“%s”      ",inputt[i]);
        for(k = 0; k < occurrences[i]/scale;k++){
            printf("*");
        }
        if(occurrences[i] == 0){
            printf("NO MATCHES");
        }
        printf("\n");


    }



}

int main(){
    FILE * fptemp = fopen("temp.txt","w");
    //double vectors[numwords()][vectorsize()];
    float threshold = 6;
    int x;
    x=numwords();
    //printf("\n%d",x);
    char dict[1001][MAX_WORD_SIZE];
    char words[300000][MAX_WORD_SIZE];
    char inputtedWord;
    char inputt[100][MAX_WORD_SIZE];
    int counter[100] = {0};
    float vecs[numwords()][vectorsize()];
    char w1[MAX_WORD_SIZE];
    char w2[MAX_WORD_SIZE];
    char hist[100][MAX_WORD_SIZE+5+20];
    int occurrences[100];

    printf("Enter text (press enter to exit):\n");
    while ((inputtedWord = getchar()) != EOF) {
        putc(inputtedWord, fptemp);
        if (inputtedWord == '\n') {
            break;
        }
    }
    fclose(fptemp);
    fptemp = fopen("temp.txt","r");
    int c,i = 0,enternum = 0;
    while(1){
        c = fgetc(fptemp);
        if(c != EOF) ungetc(c,fptemp);
        else break;
        fscanf(fptemp,"%s",inputt[i]);
        enternum++;
        i++;
    }
    enternum--;


    //read_dict(dictionary,dict);
    read_text(inputtxt,ignoretxt,words);
    vectorAdding(dictionary,dict,vecs);
    occurence(inputt,words,enternum,counter);


    // for(int j = 0;j < enternum;j++){
    //     if(counter[j] == 0){
    //         dissimilarity(inputt[j],w2,dict,threshold,vecs);
    //         for(int m = 0;m < MAX_WORD_SIZE;m++){
    //             inputt[j][m] = w2[m];
    //         }
           
    //     }
    // }

    // for(int m = 0;m < enternum;m++){
    //     for(int e = 0;e < numwords();e++){
    //         if(strcmp(inputt[m],words[e]) == 0){
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 0){
            
    //     }
        
    //     flag = 0;
    // }
    

    for(int i = 0;i < 100;i++){
        occurrences[i] = counter[i];
    }
       //////////////////////////////////////////////////////////////////////////////
    histogram(inputt,enternum,occurrences,hist);

    // for(int i = 0;i < numwords();i++){
    //     for(int k = 0;k< vectorsize();k++){
    //         //printf("%f  ",vecs[i][k]);
    //     }
    //     //printf("\n");
    // }
    

    system("rm temp.txt");
    return 0;
}