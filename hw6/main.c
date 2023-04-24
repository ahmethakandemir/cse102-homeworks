#include <stdio.h>
 
void puttingArrays(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],int productLines, int stockLines){
    FILE * products;
    FILE * stocks;
    //printf("new code\n");
    
    int c,i = 0;


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
    stockLines = 0;
    stocks = fopen("stocks.txt","r");
    while(1){
        c = fgetc(stocks);
        if(c == EOF){
            stockLines++;
            break;
        }
        else if(c == 10){
            stockLines++;
        }
    }
    fclose(stocks);
    // kesinlikle tamamlanmamis bir fikir.................................
    stocks = fopen("stocks.txt","r");
    int letter,letindex;
    for(int i = 0; i < stockLines; i++){
        
        fscanf(stocks,"%d",&sid[i]);
        //printf("sid[i] is %d",sid[i]);
        c = fgetc(stocks);
        fscanf(stocks,"%d",&stockpid[i]);
        c = fgetc(stocks);
        letindex = 0;letter = 0;
        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            branch[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 15) break;
        }

        fscanf(stocks,"%d",&current_stock[i]);

        // printf("c is= %d\n",c);
        int k = 0;

    }

    // for(int i = 0;i < stocksLines;i++){
    //     printf("\nsid is = %d\npid is = %d\nbranch is = %s\nstock is = %d\n",sid[i],stockpid[i],branch[i],current_stock[i]);
    // }
    fclose(stocks);

}


int updateTxts(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],int productLines, int stockLines){
    FILE * products = fopen("products.txt","w");
    FILE * stocks = fopen("stocks.txt","w");
    for(int i = 0;i < productLines; i++){
        fprintf(products,"%d,%c,%s,%s,%lf\n",pid[i],type[i],name[i],brand[i],price[i]);
    }
    for(int i = 0;i < stockLines; i++){
        fprintf(stocks,"%d,%d,%s,%d\n",sid[i],stockpid[i],branch[i],current_stock[i]);
    }

    fclose(products);
    fclose(stocks);

    return 0;
}

int addProduct(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],int productLines, int stockLines){
    printf("\nEnter the new product(pID is auto incremented)(type,name,brand,price): ");
    productLines++;
    scanf("%c,%s,%s,%lf",&type[productLines],name[productLines],brand[productLines],&price[productLines]);
    pid[productLines] = pid[productLines - 1] + 1;
    //printf("\n%d,%c,%s,%s,%lf",pid[productLines],type[productLines],name[productLines],brand[productLines],price[productLines]);
    updateTxts(pid,type,name,brand,price,sid,stockpid,branch,current_stock,productLines,stockLines);
    return 0;

}
void submenuFile(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],int productLines, int stockLines){
    void mainMenu(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],int productLines, int stockLines);
    printf("\n\n1- Add new product\n2- Delete a product\n3- Update a product\n4- Add feature to product\n5- Add a new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n8- Back to main menu\n\n");
    int selection;
    while(1){
        scanf("%d",&selection);
        if(selection <= 8 && selection >= 1){
            break;
        }
        else{
            printf("\nInvalid selection! Please enter your selection again! : ");
            while(getchar() != '\n');
        }
    }
    switch (selection){
    case 1: addProduct(pid,type,name,brand,price,sid,stockpid,branch,current_stock,productLines,stockLines);    break;
    case 2:     break;
    case 3:     break;
    case 4:     break;
    case 5:     break;
    case 6:     break;
    case 7:     break;
    case 8: mainMenu(pid,type,name,brand,price,sid,stockpid,branch,current_stock,productLines,stockLines);     break;
    default:    break;
    }
}

void mainMenu(int pid[100],char type[100],char name[100][9],char brand[100][6],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],int productLines, int stockLines){
    int selection;
    printf("\n\nMain Menu:\n1- File Operations\n2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n\nPlease make a selection: ");
    while(1){
        scanf("%d",&selection);
        if(selection <= 5 && selection >= 1){
            break;
        }
        else{
            printf("\nInvalid selection! Please enter your selection again! : ");
            while(getchar() != '\n');
        }
    }

    switch (selection){
    case 1:submenuFile(pid,type,name,brand,price,sid,stockpid,branch,current_stock,productLines,stockLines);break;
    case 2:     break;
    case 3:     break;
    case 4:     break;
    case 5:     break;
    default:    break;
    }
}











int main(){
    int productLines = 0;
    int stockLines = 0;
    // product.txt arrays
    int pid[100] = {0};
    char type[100] = {0};
    char name[100][9] = {0};
    char brand[100][6] = {0};
    double price[100] = {0};
    // stocks.txt arrays
    int stockpid[100] = {0};
    int sid[100] = {0};
    char branch[100][15] = {0};
    int current_stock[100] = {0};

    puttingArrays(pid,type,name,brand,price,sid,stockpid,branch,current_stock,0,0);
    printf("\n\n%d\n\n",productLines);
    mainMenu(pid,type,name,brand,price,sid,stockpid,branch,current_stock,productLines,stockLines);


}
