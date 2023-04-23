#include <stdio.h>
 

// int sid[100];
// char branch[100][15];
// int current_stock[100];



void puttingArrays(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100]){
    FILE * products;
    printf("new code\n");
    
    int c,productLines = 0,i = 0;

    products = fopen("products.txt","r");
    while(1){
        c = fgetc(products);
        if(c == EOF){
            productLines++;
            break;
        }
        else if(c == 10){
            productLines++;
        }
        
    }

    fclose(products);
    products = fopen("products.txt","r");

    for(int i = 0; i < productLines; i++) 
    {
        int letter = 0,letindex = 0;
        
        fscanf(products,"%d",&pid[i]);
        c = fgetc(products);
        fscanf(products,"%c",&type[i]);
        c = fgetc(products); // c = ','


        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            name[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 9) break;
        }
        letindex = 0;letter = 0;
        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            brand[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 6) break;
        }
        c = fgetc(products);

        fscanf(products,"%lf",&price[i]);
        
        c = fgetc(products);
        //printf("\nc is :: %c\n",c);

        
        if(c == EOF){
            break;
        }
        else if(c == 10){
            continue;
        }


    }

    fclose(products);
    

}
int main(){
    int pid[100] = {0};
    char type[100] = {0};
    char name[100][9] = {0};
    char brand[100][6] = {0};
    double price[100] = {0};

    puttingArrays(pid,type,name,brand,price);
    
    for(int i = 0;i< 2;i++)
        printf("\n pid is : %d\n type is : %c\n name is : %s\n brand is : %s\n price is : %lf\n\n",pid[i],type[i],name[i], brand[i], price[i]);
}
