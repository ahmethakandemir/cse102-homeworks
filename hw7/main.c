#include <stdio.h>
#include <string.h>
const char dictionary[20] = "dictionary.txt";


#define MAX_WORD_SIZE 12
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


int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
    FILE * fpdict;
    fpdict = fopen(file_name, "r");
    int c,i,k;
    while (c != 10){
        c = fgetc(fpdict);
        //printf("%c",c);
    }
    //printf("%d\n",numwords());
    for(i = 0; i < numwords(); i++){

        k = 0;
        while(1){
            c = fgetc(fpdict);
            if(c == EOF || c == 32){
                printf("\ndeme, c = %c",c);

                break;
            }

            dict[i][k] = c;
            printf("\n2.  %c",c);
            k++;

                
        }

        while (c != 10){
            c = fgetc(fpdict);
        }
        printf("\n i = %d",i);
        //printf("\n%s",dict[i]);
    }
    dict[i+1][0] = '-';




    fclose(fpdict);
    return 0;
}



int main(){
    double vectors[numwords()][vectorsize()];
    char dict[numwords() + 1][MAX_WORD_SIZE];
    read_dict(dictionary,dict);


    return 0;
}
