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
int featurecounter(){
    FILE * products = fopen("products.txt","r");
    int c,counter = 1;
    while(1){
        c = fgetc(products);
        if(c == 10){
            break;
        }
        else if(c == 44){
            counter++;
        }
    }
    fclose(products);
    //printf("counter is: %d",counter);
    return counter;
}
void puttingArrays(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],char newfeatures[5][100][15]){
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

int updateProdArrays(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int deletion,char newfeatures[5][100][15]){
    
    int productLines = productLinesfunc();
    if(deletion){
        productLines--;
    }
    FILE * products = fopen("products.txt","w");
    for(int i = 0;i < productLines; i++){
        fprintf(products,"%d,%c,%s,%s,%.2lf",pid[i],type[i],name[i],brand[i],price[i]);
        if(featurecounter() > 5){
            fprintf(products,",%s",newfeatures[featurecounter() - 5][i]);
        }
        if(i < productLines - 1){
            fprintf(products,"\n");
        }
    }
    fclose(products);
    return 0;
}

int updateProduct(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],char newfeatures[5][100][15]){

    int upid;
    char upfeature[10];
    printf("\nenter the pid of the product you want to update: ");

    while(1){
        scanf("%d",&upid);
        if(upid < 1 || upid > productLinesfunc()){
            printf("\nInvalid selection! Please enter your selection again! : ");
            while(getchar() != '\n'); 
        }
        else{
            break;
        }
    }
    printf("\nwhich feature you want to update?(pid can't be changed): ");
    while(1){

        scanf("%s",upfeature);
        for(int i = 0;i < 6;i++){
            if (upfeature[i] <= 90 && upfeature[i] >= 65){
                upfeature[i] += 32;
            }
            else if(upfeature[i] <= 122 && upfeature[i] >= 97){}
        }

    if(upfeature[0] == 't'){
        char k;
        printf("\nenter the new type for the product: ");
        scanf(" %c",&k);
        type[upid - 1] = k;
        break;
    }
    else if(upfeature[0] == 'n'){
        printf("\nenter the new name for the product: ");
        char k[15];
        scanf(" %s",k);
        for(int i = 0; i < 15;i++){
            name[upid - 1][i] = k[i]; 
        }
        break;
    }
    else if(upfeature[0] == 'b'){
        printf("\nenter the new brand for the product: ");
        char k[15];
        scanf(" %s",k);
        for(int i = 0; i < 15;i++){
            brand[upid - 1][i] = k[i]; 
        }
        break;
    }
    else if(upfeature[0] == 'p'){
        printf("\nenter the new price for the product: ");
        double k;
        scanf("%lf",&k);
        price[upid - 1] = k;
        break;
    }
    else{
        printf("\nError getting the feature!!!, please enter again: \n");
    }
    }    

    updateProdArrays(pid,type,name,brand,price,0,newfeatures);
    return 0;
}



int addProduct(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],char newfeatures[5][100][15]){
    printf("\nEnter the new product(pID is auto incremented)(type,name,brand,price): ");
    FILE * products = fopen("products.txt","a");
    int productLines = productLinesfunc();
    char temptype,tempname[15],tempbrand[15];
    double tempprice;
    scanf(" %c,%[^,],%[^,],%lf", &temptype, tempname, tempbrand, &tempprice);
    //printf("\ntemps : type = %c , name = %s, brand = %s, price = %.1lf\n",temptype,tempname,tempbrand,tempprice);
    fprintf(products,"\n%d,%c,%s,%s,%lf",productLines + 1,temptype,tempname,tempbrand,tempprice);
    //printf("\n%d,%c,%s,%s,%lf",pid[productLines],type[productLines],name[productLines],brand[productLines],price[productLines]);
	fclose(products);
    puttingArrays(pid,type,name,brand,price,sid,stockpid,branch,current_stock,newfeatures);
    // products = fopen("products.txt","r");
    // for(int i = 0;i < productLinesfunc();i++)
    //     printf("\n%d,%c,%s,%s,%.2lf\n",pid[i],type[i], name[i], brand[i],price[i]);
    // fclose(products);
    return 0;
}

int deleteProduct(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],char newfeatures[5][100][15]){
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
            for (int j = i; j < productLinesfunc(); j++) {
                //pid[j] = pid[j+1];
                type[j] = type[j + 1];
                for(int k = 0;k < 14;k++){
                    name[j][k] = name[j + 1][k];
                }
                for(int k = 0;k < 14;k++){
                    brand[j][k] = brand[j + 1][k];
                }
                price[j] = price[j + 1];
            }
            break;
        }
    }
    updateProdArrays(pid,type,name,brand,price,1,newfeatures);
    return 0;
}



int addFeature(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],char newfeatures[5][100][15]){
    printf("\nenter the name of the feature you want to add to all products: ");
    char featureName[15];
    scanf("%s",featureName);
    int features = featurecounter() - 5;
    for(int i = 0; i < 100;i++){
        for(int j = 0; j < 15;j++)
            newfeatures[features][i][j] = 0; // try \n if it doesnt work
    }
    //updateProdArrays(pid,type,name,brand,price,0,newfeatures);
    

    return 0;
}


void submenuFile(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],char newfeatures[5][100][15]){
    void mainMenu(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],char newfeatures[5][100][15]);
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
    case 1: addProduct(pid,type,name,brand,price,sid,stockpid,branch,current_stock,newfeatures);break;
    case 2: deleteProduct(pid,type,name,brand,price,newfeatures);break;
    case 3: updateProduct(pid,type,name,brand,price,newfeatures);break;
    case 4: addFeature(pid,type,name,brand,price,newfeatures);    break;
    case 5:     break;
    case 6:     break;
    case 7:     break;
    case 8:     break;
    default:    break;
    }
    mainMenu(pid,type,name,brand,price,sid,stockpid,branch,current_stock,newfeatures);
}

void mainMenu(int pid[100],char type[100],char name[100][15],char brand[100][15],double price[100],int sid[100],int stockpid[100],char branch[100][15],int current_stock[100],char newfeatures[5][100][15]){
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
    case 1:submenuFile(pid,type,name,brand,price,sid,stockpid,branch,current_stock,newfeatures);break;
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
    // if user wants to add new features, this array will storage it.
    char newfeatures[5][100][15] = {0};
    int counter = 0;
    puttingArrays(pid,type,name,brand,price,sid,stockpid,branch,current_stock,newfeatures);

    mainMenu(pid,type,name,brand,price,sid,stockpid,branch,current_stock,newfeatures);
    

}
