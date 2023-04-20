#include <stdio.h>
int part1();
int lowercase(int);

int main(){
    part1();

}



int part1(){
    printf("Welcome to part1!!\n\n");
    FILE* myfile;
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int counts[26] = {0};
    char input[30];
    printf("Input file name: ");
    scanf("%s",input);
    myfile = fopen(input,"r");

    if(myfile == NULL){
        perror("Error opening file");
        return 0;
    }
    
    printf("Letter frequency: \n");
    while(1){
        int c = fgetc(myfile);
        if(c == EOF){
            break;
        }
        for(int i = 0;i < 26; i++){
            if(c == letters[i]){
                counts[i]++;
            }
            if(c <= 90 && c >= 65){
                if(lowercase(c) == letters[i]){
                    counts[i]++;
                }    
            }
        }
    }

    for(int i = 0;i < 26; i++){
        printf("%c : %d\n",letters[i] - 32,counts[i]);
    }
    return 0;
}
int lowercase(int c){
    return (c += 32);
}
