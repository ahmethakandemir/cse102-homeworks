#include <stdio.h>
#include <string.h>
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
int read_dict(const char *  file_name, char dict[][MAX_WORD_SIZE]){
	int i,j=0,c=0,numss,vectorss;
	char temp;
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
			printf("%.1f ", vecs[i][j]);
		}
		printf("\n");
	}
    for(i = 0;i < numwords(); i++){
        printf("%s ",dict[i]);
    }
	return numss;	
}
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]){
    FILE * fpinput;
    FILE * fpignore;
    char ignore[100][MAX_WORD_SIZE];
    fpinput = fopen(text_file,"r");
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
    int c;
    while(1){
        fscanf(fpinput,"%s",words[i]);
        c = fgetc(fpinput);
        while((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57)){
            ungetc(c,fpinput);
        }
        
        
        i++;
    }




    
    fclose(fpinput);
    
    return 0;


}

int main(){
    double vectors[numwords()][vectorsize()];
    char dict[numwords() + 1][MAX_WORD_SIZE];
    char words[300000][MAX_WORD_SIZE];



    //read_dict(dictionary,dict);
    read_text(inputtxt,ignoretxt,words);


    return 0;
}
