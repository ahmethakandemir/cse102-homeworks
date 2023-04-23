#include <stdio.h>
FILE * products;
FILE * stocks;  

int pid[100];
char type[100];
char name[100][8];
char brand[100][5];
double price[100];

int sid[100];
char branch[100][15];
int current_stock[100];

void puttingArrays(){
    products = fopen("products.txt","r");
    stocks = fopen("stocks.txt","r");
    int c,productLines = 0,pid;
    fscanf(products,"%d",&pid);
    while (1)   // getting the line count
    {
        c = fgetc(products);
        if(c == EOF){
            productLines++;
            break;
        }
        else if(c == '\n'){
            productLines++;
        }
    }
    printf("%d",productLines);


    fclose(products);
    fclose(stocks);
}






int main(){
    puttingArrays();
}

