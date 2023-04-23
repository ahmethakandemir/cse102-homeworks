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
    int c,productLines = 0,i = 0,letter = 0,letindex = 0;
    while (1)   // getting the line count
    {

        fscanf(products,"%d",&pid[i]);
        fgetc(products);
        fscanf(products,"%c",&type[i]);
        fgetc(products); // c = ','


        while ((letter = fgetc(products)) != ',' && letter != '\n' && letter != EOF) {
            name[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 8) break;  /* prevent writing beyond array */
        }
        letindex = 0;
        fgetc(products);
        fscanf(products,"%s",brand[i]);
        fgetc(products);
        fscanf(products,"%lf",&price[i]);
        c = fgetc(products);

        if(c == EOF){
            productLines++;
            break;
        }
        else if(c == '\n'){
            productLines++;
        }
        i++;
    }

    printf("%s",name[i]);

    fclose(products);
    fclose(stocks);
}






int main(){
    puttingArrays();
}

