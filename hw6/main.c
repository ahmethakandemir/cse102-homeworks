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
        if(c == EOF){
            break;
        }
    }
    fclose(products);
    return counter;
}
int puttingArraysProd(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){
    FILE * products;
    
    //printf("new code\n");
    
    int c,i = 0,flag = 0;

    products = fopen("products.txt","r");
    int productLines = productLinesfunc();
    for(int i = 0; i < productLines + 1; i++) 
    {
        int letter = 0,letindex = 0;
        
        fscanf(products,"%d",& intArrays[0][i]);
        c = fgetc(products);
        fscanf(products,"%c",&charArrays[0][i][0]);
        c = fgetc(products); // c = ','


        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            charArrays[1][i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 15) break;
        }
        letindex = 0;letter = 0;
        while ((letter = fgetc(products)) != ',' && letter != '\n') {
            charArrays[2][i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 15) break;
        }

        fscanf(products,"%lf",&prices[i]);
        c = fgetc(products);
        if(c == EOF)break;
        int k = 6;
        
            if(c == 44){
                fscanf(products,"%s",charArrays[k][i]);
                fgetc(products);
            }
            else{
                break;
            }
        


    }
    fclose(products);
    return 0;
}

int puttingArraysStocks(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){

    FILE * stocks;
    // kesinlikle tamamlanmamis bir fikir.................................
    stocks = fopen("stocks.txt","r");
    int letter,letindex,c;
    int stockLines = stockLinesfunc();
    for(int i = 0; i < stockLinesfunc(); i++){
        
        fscanf(stocks,"%d",&intArrays[1][i]);
        //printf("sid[i] is %d",sid[i]);
        c = fgetc(stocks);
        fscanf(stocks,"%d",&intArrays[2][i]);
        c = fgetc(stocks);
        letindex = 0;letter = 0;
        while ((letter = fgetc(stocks)) != ',' && letter != '\n') {
            charArrays[3][i][letindex] = letter;
            letindex++;
            if (letindex + 1 == 15) break;
        }

        fscanf(stocks,"%d",&intArrays[3][i]);

        // printf("c is= %d\n",c);
        int k = 0;

    }

    // for(int i = 0;i < stocksLines;i++){
    //     printf("\nsid is = %d\npid is = %d\nbranch is = %s\nstock is = %d\n",sid[i],stockpid[i],branch[i],current_stock[i]);
    // }
    fclose(stocks);
    return 0;
}
int updateProdFile(char charArrays[10][100][15],double prices[100],int intArrays[10][100],int deletion){
    int productLines = productLinesfunc();
    int features = featurecounter();
    if(deletion){
        productLines--;
    }
    //printf("  %d   ",featurecounter());
    FILE * products = fopen("products.txt","w");
    for(int i = 0;i < productLines; i++){
        fprintf(products,"%d,%c,%s,%s,%.2lf",intArrays[0][i],charArrays[0][i][0],charArrays[1][i],charArrays[2][i],prices[i]);
            //printf("enteredd");
        for(int k = 5;k < features;k++){
            if(charArrays[k][i][0] == 0){
                fprintf(products,",None");
            }
            else{
                fprintf(products,"%s",charArrays[k + 1][i]);
            }
        }  
        if(i < productLines - 1){
            fprintf(products,"\n");
        }
    }
    fclose(products);

    return 0;
    //charArrays[4][k] != NULL
}

int addProduct(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){
    int features = featurecounter();
    printf("\nEnter the new product(pID is auto incremented)(type,name,brand,price");
    for(int i = 6;i < features + 1;i++){
        //printf("feature counter is : %d",featurecounter());
        if(i < features + 1){
            printf(",");
        }
        printf("%s",charArrays[4][i]);
    }
    printf("): ");

    FILE * products = fopen("products.txt","a");
    int productLines = productLinesfunc();
    char tempinput[100];
    scanf("%s",tempinput);
    int counter = 2;
    fprintf(products,"\n%d,%s",productLines + 1,tempinput);

    // for(int i = 0;i < 100; i++){
    //     if(tempinput[i] == 44){
    //         counter++;
    //     }
    // }
    // for(int i = 0;i < 5;i++){

    // }


    // for(int i = 5; i < counter;i++){
    //     charArrays[i][productLines + 1];
    // }
    
    //scanf(" %c,%[^,],%[^,],%lf", &temptype, tempname, tempbrand, &tempprice);
    //printf("\ntemps : type = %c , name = %s, brand = %s, price = %.1lf\n",temptype,tempname,tempbrand,tempprice);
    //fprintf(products,"\n%d,%c,%s,%s,%lf",productLines + 1,temptype,tempname,tempbrand,tempprice);
    //printf("\n%d,%c,%s,%s,%lf",pid[productLines],type[productLines],name[productLines],brand[productLines],price[productLines]);
	fclose(products);
    puttingArraysProd(charArrays,prices,intArrays);
    
    // products = fopen("products.txt","r");
    // for(int i = 0;i < productLinesfunc();i++)
    //     printf("\n%d,%c,%s,%s,%.2lf\n",intArrays[0][i],charArrays[0][i][0],charArrays[1][i], charArrays[2][i],prices[i]);
    // fclose(products);
    return 0;
}
int addFeature(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){
    for(int i = 0;i <= 5;i++){
        charArrays[4][i][0] = 'a';
    } 
    printf("\nenter the name of the feature you want to add to all products: ");
    scanf("%s",charArrays[4][featurecounter() + 1]);
    //intArrays[4][0] = featurecounter() + 1;

    updateProdFile(charArrays,prices,intArrays,0);
    

    return 0;
}

int deleteProduct(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){
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
        if(deletedpid == intArrays[0][i]){
            for (int j = i; j < productLinesfunc(); j++) {
                //pid[j] = pid[j+1];
                charArrays[0][j][0] = charArrays[0][j + 1][0];
                for(int k = 0;k < 14;k++){
                    charArrays[1][j][k] = charArrays[1][j + 1][k];
                }
                for(int k = 0;k < 14;k++){
                    charArrays[2][j][k] = charArrays[2][j + 1][k];
                }
                prices[j] = prices[j + 1];
                for(int k = 0;k < 14;k++){
                    for(int m = 5;m < 10;m++){
                        charArrays[m][j][k] = charArrays[m][j + 1][k];
                    }
                }
            }
            break;
        }
    }
    updateProdFile(charArrays,prices,intArrays,1);
    return 0;
}

int updateProduct(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){

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
        charArrays[0][upid - 1][0] = k;
        break;
    }
    else if(upfeature[0] == 'n'){
        printf("\nenter the new name for the product: ");
        char k[15];
        scanf(" %s",k);
        for(int i = 0; i < 15;i++){
            charArrays[1][upid - 1][i] = k[i]; 
        }
        break;
    }
    else if(upfeature[0] == 'b'){
        printf("\nenter the new brand for the product: ");
        char k[15];
        scanf(" %s",k);
        for(int i = 0; i < 15;i++){
            charArrays[2][upid - 1][i] = k[i]; 
        }
        break;
    }
    else if(upfeature[0] == 'p'){
        printf("\nenter the new price for the product: ");
        double k;
        scanf("%lf",&k);
        prices[upid - 1] = k;
        break;
    }
    else{
        printf("\nError getting the feature!!!, please enter again: \n");
    }
    }    
    updateProdFile(charArrays,prices,intArrays,0);
    return 0;
}

void submenuFile(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){
    void mainMenu(char charArrays[10][100][15],double prices[100],int intArrays[10][100]);
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
    case 1: addProduct(charArrays,prices,intArrays);break;
    case 2: deleteProduct(charArrays,prices,intArrays);break;
    case 3: updateProduct(charArrays,prices,intArrays);break;
    case 4: addFeature(charArrays,prices,intArrays);    break;
    case 5:     break;
    case 6:     break;
    case 7:     break;
    case 8:     break;
    default:    break;
    }
    mainMenu(charArrays, prices,intArrays);
}



void mainMenu(char charArrays[10][100][15],double prices[100],int intArrays[10][100]){
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
    case 1:submenuFile(charArrays, prices,intArrays);break;
    case 2:     break;
    case 3:     break;
    case 4:     break;
    case 5:     break;
    default:    break;
    }
}






int main(){
    // 0 = type/ 1 = name/ 2 = brand/ 3 = branch
    char charArrays[10][100][15] = {0}; 
    
    double  prices[100] = {0};
    //0 = pID/ 1 = sID/ 2 = stockpID/ 3 = stock/
    int intArrays[10][100] = {0};
    
    puttingArraysProd(charArrays, prices,intArrays);
    mainMenu(charArrays, prices,intArrays);
}