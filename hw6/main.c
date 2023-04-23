#include <stdio.h>
 

// int sid[100];
// char branch[100][15];
// int current_stock[100];



void puttingArrays(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100]){
    FILE * products = fopen("products.txt","r");
    FILE * stocks = fopen("stocks.txt","r");
    
    int c,productLines = 0,i = 0;
    while (1)   // getting the line count
    {
        int letter = 0,letindex = 0;
        fscanf(products,"%d",&pid[i]);
        c = fgetc(products);
        fscanf(products,"%c",&type[i]);
        c = fgetc(products); // c = ','


        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            name[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 9) break;  /* prevent writing beyond array */
        }
        letindex = 0;letter = 0;
        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            brand[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 6) break;  /* prevent writing beyond array */
        }
        //printf("\nc is :: %c\n",c);
        fscanf(products,"%lf",&price[i]);
        c = fgetc(products);
        //printf("\nc is :: %c\n",c);
        i++;

        if(c == EOF){
            productLines++;
            break;
        }
        if(c == '\n'){
            printf("newline"); // girmiyorrrrrrrrr
            productLines++;
        }

    }

    fclose(products);
    fclose(stocks);

}
int main(){
    int pid[100] = 0;
    char type[100] = 0;
    char name[100][9] = 0;
    char brand[100][6] = 0;
    double price[100] = 0;

    puttingArrays(pid,type,name,brand,price);
    
    for(int i = 0;i< 2;i++)
        printf("\n pid is : %d\n type is : %c\n name is : %s\n brand is : %s\n price is : %lf\n\n",pid[i],type[i],name[i], brand[i], price[i]);
}