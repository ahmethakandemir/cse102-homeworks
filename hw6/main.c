#include <stdio.h>
 
int stockLinesfunc(){
    FILE * stocks;
    int stockLinecount = 0,c;
    stocks = fopen("stocks.txt","r");
    while(1){
        c = fgetc(stocks);
        if(c == EOF){
            stockLinecount++;
            break;
        }
        else if(c == 10){
            stockLinecount++;
        }
    }
    fclose(stocks);
    return stockLinecount;
}

int productLinesfunc(){
    FILE * products;
    int productsLinecount = 0,c;
    products = fopen("products.txt","r");
    while(1){
        c = fgetc(products);
        if(c == EOF){
            productsLinecount++;
            break;
        }
        else if(c == 10){
            productsLinecount++;
        }
    }
    fclose(products);
    return productsLinecount;
}
void puttingArrays(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100]){
    FILE * products;
    FILE * stocks;
    //printf("new code\n");
    
    int c,i = 0;

    products = fopen("products.txt","r");
    int productLines = productLinesfunc();
    for(int i = 0; i < productLines + 1; i++) 
    {
        int letter = 0,letindex = 0;
        
        fscanf(products,"%d",&pid[i]);
        c = fgetc(products);
        fscanf(products,"%c",&type[i]);
        c = fgetc(products); // c = ','


        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            name[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 15) break;
        }
        letindex = 0;letter = 0;
        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            brand[i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 15) break;
        }

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

    // kesinlikle tamamlanmamis bir fikir.................................
    stocks = fopen("stocks.txt","r");
    int letter,letindex;
    int stockLines = stockLinesfunc();
    for(int i = 0; i < stockLinesfunc(); i++){
        
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


int updateProdArrays(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100]){
    int productLines = productLinesfunc();
    FILE * products = fopen("products.txt","w");
    for(int i = 0;i < productLines; i++){
        fprintf(products,"%d,%c,%s,%s,%lf",pid[i],type[i],name[i],brand[i],price[i]);
        if(i < productLines - 1){
            fprintf(products,"\n");
        }
    }
    fclose(products);
    return 0;
}

int addProduct(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100]){
    printf("\nEnter the new product(pID is auto incremented)(type,name,brand,price): ");
    FILE * products = fopen("products.txt","a");
    int productLines = productLinesfunc();
    char temptype,tempname[15],tempbrand[15];
    double tempprice;
    scanf(" %c,%[^,],%[^,],%lf", &temptype, tempname, tempbrand, &tempprice);
    printf("\ntemps : type = %c , name = %s, brand = %s, price = %.1lf\n",temptype,tempname,tempbrand,tempprice);
    fprintf(products,"\n%d,%c,%s,%s,%lf",productLines + 1,temptype,tempname,tempbrand,tempprice);
    //printf("\n%d,%c,%s,%s,%lf",pid[productLines],type[productLines],name[productLines],brand[productLines],price[productLines]);
	fclose(products);
    puttingArrays(pid,type,name,brand,price,sid,stockpid,branch,current_stock);
    products = fopen("products.txt","r");
    for(int i = 0;i < productLinesfunc();i++)
        printf("\n%d,%c,%s,%s,%.2lf\n",pid[i],type[i], name[i], brand[i],price[i]);
    fclose(products);
    return 0;
}

int deleteProduct(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100]){
    int deletedpid;
    printf("\nEnter the pID of the product you want to delete: ");
    while(1){
        scanf("%d",&deletedpid);
        if(deletedpid < 1 || deletedpid > productLinesfunc()){
            printf("\nInvalid selection! Please enter your selection again! : ");
            while(getchar() != '\n'); 
        }
        else{
            break;
        }
    }
    for(int i = 0; i < productLinesfunc(); i++){
        if(deletedpid == pid[i]){
            for (int j = i; j < productLinesfunc() - 1; j++) {
                pid[j] = pid[j+1];
                strcpy(type[j], type[j+1]);
                strcpy(name[j], name[j+1]);
                strcpy(brand[j], brand[j+1]);
                price[j] = price[j+1];
            }
            break;
        }
    }

    return 0;
}
void submenuFile(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100]){
    void mainMenu(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100]);
    printf("\n\n1- Add new product\n2- Delete a product\n3- Update a product\n4- Add feature to product\n5- Add a new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n8- Back to main menu\n\n");
    int selection;
    while(1){
        printf("Please make a selection: ");
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
    case 1: addProduct(pid,type,name,brand,price,sid,stockpid,branch,current_stock);    break;
    case 2: deleteProduct(pid,type,name,brand,price);   break;
    case 3:     break;
    case 4:     break;
    case 5:     break;
    case 6:     break;
    case 7: updateProdArrays(pid,type,name,brand,price);    break;
    case 8: mainMenu(pid,type,name,brand,price,sid,stockpid,branch,current_stock);     break;
    default:    break;
    }
}

void mainMenu(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100]){
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
    case 1:submenuFile(pid,type,name,brand,price,sid,stockpid,branch,current_stock);break;
    case 2:     break;
    case 3:     break;
    case 4:     break;
    case 5:     break;
    default:    break;
    }
}


int main(){

    // product.txt arrays
    int pid[100] = {0};
    char type[100] = {0};
    char name[100][15] = {0};
    char brand[100][15] = {0};
    double price[100] = {0};
    // stocks.txt arrays
    int stockpid[100] = {0};
    int sid[100] = {0};
    char branch[100][15] = {0};
    int current_stock[100] = {0};

    puttingArrays(pid,type,name,brand,price,sid,stockpid,branch,current_stock);

    mainMenu(pid,type,name,brand,price,sid,stockpid,branch,current_stock);


}
