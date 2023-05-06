#include <stdio.h>
#include <string.h>
FILE * dict;

int numwords(){
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

int main(){

    printf("vectorsize = %d\n",vectorsize());
    printf("numwords = %d\n",numwords());
    return 0;
}
