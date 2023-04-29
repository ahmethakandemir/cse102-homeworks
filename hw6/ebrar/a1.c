#include <stdio.h>
int fillarrays(int pid[100], char brand[100][8],char name[100][5],double price[100],char type[100], FILE *products){ 
  
   products = fopen("product.txt","r");
    int c;
	int nl = -1, i;
	
	while(1){
    	c = fgetc(products);
		//printf("\n%c\n",c);
    	if(c == EOF){
    		nl++;
    		break;	
    	}	
    	if(c == 10){
    		nl++;
    	}	
    }
    fclose(products);
    products = fopen("product.txt","r");
	i=0;
	
    for(int i = 0; i < nl; i++){
    	fscanf(products,"%d,%c,%s,%s,%lf", &pid[i], &type[i], name[i], brand[i], &price[i]);
    }



    fclose(products);
    return 0;

}

int addproduct(int pid[100], char brand[100][8],char name[100][5],double price[100],char type[100], FILE *products){
	int c, nl=-1; 
	products = fopen("product.txt", "r+");     
	if(products==NULL){
		printf("\nError in opening this file");
	}
    while(1){
    	c = fgetc(products);
    	if(c == EOF){
    		nl++;
    		break;	
    	}	
    	if(c == 10)
    		nl++;
    }
    fclose(products);
    printf("\nYou are about to add a new product to prouct list.\npID will be automaticly incremented");
    printf("\nPlease enter the type of the product (D,F,C,O): ");
    scanf(" %c", &type[nl]);
    printf("\nPlease enter the name of the product (maximum 5 letters): ");
    scanf("%s", name[nl]);
    printf("\nPlease enter the brand name (maximum 8 letters): ");
    scanf("%s", brand[nl]);
    printf("\nPlease enter the price of the product: ");
    scanf("%lf", &price[nl]);
  
    products = fopen("product.txt", "r+");     
	if(products==NULL){
		printf("\nError in opening this file");
	}
    while(1){
    	c = fgetc(products);
  		
    	if(c == EOF){
    		fprintf(products,"%d,%c,%s,%s,%.2lf\n", nl, type[nl], name[nl], brand[nl], price[nl]);
    		break;	  	
        }
    }    
    fclose(products);//direkt while ı silip yapabilirsin
    //fseek(products, 0, SEEK_END);
    //fprintf(products,"%d,%c,%s,%s,%lf\n", nl, type[nl], name[nl], brand[nl], price[nl]);
    //fclose(products);
    return fillarrays(pid, brand, name, price, type, products);
}
int deleteproduct(int pid[100], char brand[100][8],char name[100][5],double price[100],char type[100], FILE *products){
	printf("\nYou are about to delete a product from the file");
	int pd;
	printf("\nPlease enter the pID of the product that you want to delete: ");
	scanf("%d", &pd);
	//pid var olan değerlerden büyükse hata kodu
	int c, nl=-1, i; 
	products = fopen("product.txt", "r+");     
	if(products==NULL){
		printf("\nError in opening this file");
	}
    while(1){
    	c = fgetc(products);
    	if(c == EOF){
    		nl++;
    		break;	
    	}	
    	if(c == 10){
    		nl++;
    	}
    	if(nl == pd){
    		i=1;
    		printf("a");
    		while(pid[pd+i]!='\0'){
    			printf("a");
    			fprintf(products,"%d,%c,%s,%s,%.2lf\n", pd+i-1, type[pd+i], name[pd+i], brand[pd+i], price[pd+i]);
    			i++;
    		}
    	}	
    }
    fclose(products);
}

int main(){
	FILE *fproduct = NULL;
	int i;
	int pid[100]={0};
	char brand[100][8]={0};
	char name[100][5]={0};
	double price[100]={0};
	char type[100]={0};
	
	addproduct(pid,brand,name,price,type,fproduct);
	//deleteproduct(pid,brand,name,price,type,fproduct);
	for(int i = 0;i< 8;i++)
        printf("\n pid is : %d\n type is : %c\n name is: %s\n brand is: %s\n price is : %lf\n\n",pid[i],type[i], name[i], brand[i],price[i]);
	return 0;
	
}
