#include <stdio.h>
 
void puttingArrays(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100]){
    FILE * products;
    FILE * stocks;
    //printf("new code\n");
    
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
            if (letindex + 1 == 10) break;
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
    int stocksLines = 0;
    stocks = fopen("stocks.txt","r");
    while(1){
        c = fgetc(stocks);
        if(c == EOF){
            stocksLines++;
            break;
        }
        else if(c == 10){
            stocksLines++;
        }
    }

    // kesinlikle tamamlanmamis bir fikir.................................
    int matcher,matcherindex;
    for(int i = 0; i < 1; i++){
        fscanf(stocks,"%d",&sid[i]);
        printf("sid[0] is %d",sid[i]);
        fscanf(stocks,"%d",&matcher);
        printf("\nmatcher is: %d\n",matcher);
        c = fgetc(stocks);
        int k = 0;
        while(1){
            if(pid[k] == 0){
                printf("\nno match for this item in product.txt\n");
                break;
            }
            else if(matcher == pid[k]){
                matcherindex = k;
                break;
            }
            else{
                k++;
            }
        }
    }
    printf("sid[0] = %d \n",sid[0]);


    fclose(stocks);

}



int main(){
    // product.txt arrays
    int pid[100] = {0};
    char type[100] = {0};
    char name[100][9] = {0};
    char brand[100][6] = {0};
    double price[100] = {0};
    // stocks.txt arrays
    int sid[100] = {0};
    char branch[100][15] = {0};
    int current_stock[100] = {0};

    puttingArrays(pid,type,name,brand,price,sid);
    
    // for(int i = 0;i< 4;i++){
    //     printf("\n pid is : %d\n type is : %c\n name is : %s\n brand is : %s\n price is : %lf\n\n",pid[i],type[i],name[i], brand[i], price[i]);
    // }

}
