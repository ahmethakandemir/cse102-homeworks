#include <stdio.h>
int menuing();
float selecting();

FILE * fmenu;
FILE * fbill;

int main(){
    menuing();
    selecting();

}

float selecting(){

    fbill = fopen("bill.txt","w");
    fclose(fbill);

    float price;
    int c,i,servings;
    while(1){
        int boslukcu = 1;
        int choose = 99;
        while (choose < 1 || choose > 10){
            printf("\nPlease choose a product (1-10): ");
            scanf("%d",&choose);
            if((choose < 1 || choose > 10)){
                printf("Please enter a valid selection!!\n");
            }
            getchar();
        }

        printf("\n");
        printf("How many servings do you want?: ");
        scanf("%d",&servings);

        if(servings == 0){
            return 0;
        }
        else{

            fbill = fopen("bill.txt","a+");
            fmenu = fopen("menu.txt","r");
            for(i = 0; i < choose - 1;i++){
                while ((c = fgetc(fmenu)) != EOF){
                    if(c == 10){
                        break;
                    }
                }
            }

            if(servings > 1){
                fprintf(fbill,"%d* ",servings);
                boslukcu += 3;
            }

            while ((c = fgetc(fmenu)) != 32){
                fprintf(fbill, "%c",c);
                boslukcu++;
            }

            fprintf(fbill," ");
            
            fscanf(fmenu,"%f",&price);
            
            fclose(fmenu);

            price *= servings;
            for(i = 0; i < 12 - boslukcu ;i++){
                fprintf(fbill," ");
            }
            fprintf(fbill,"%.2f\n",price);
            fclose(fbill);
        }
    }
    return 1;
}



int menuing(){
    fmenu = fopen("menu.txt","r");
    int i = 1;
    printf("Yemek Listesi:\n");
    printf("1. ");
    while (1){   
        while(1){
            int c = fgetc(fmenu);
            if(c == EOF){
                printf("\n");
                return 0;
            }
            if((c >= 48 && c <= 57) || c == 46){}
            else{
                printf("%c",c);
            }
            if(c == 10){
                i++;
                printf("%d. ",i);
            }
        }

    }


    fclose(fmenu);

    printf("\n\n");
    return 0;
}