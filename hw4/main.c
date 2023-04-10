#include <stdio.h>
#include <time.h>

int menuing();
int billing();
float total(float sum);
void billtoterminal();

FILE * fmenu;
FILE * fbill;

int main(){
    menuing();
    billing();
}

void billtoterminal(){
    fbill = fopen("bill.txt","r");
    int c;
    printf("\n\nHere is your bill: \n\n");
    while(1){
        c = fgetc(fbill);
        if(c == EOF){
            break;
        }
        printf("%c",c);
    }
    printf("\n");
    fclose(fbill);
}


float total(float sum){
    char student;
    float disc;
    int flag = 0;
    float vat;
    fbill = fopen("bill.txt","a");
    fprintf(fbill,"Total:                        %.2f",sum);

    while(!flag){

        printf("Are you student? (Y/N):");
        scanf(" %c",&student);
        switch (student)
        {
        case 'y':
        case 'Y':
            disc = sum * 12.5 / 100;
            sum -= disc;
            fprintf(fbill,"\nStudent Discount:            -%.2f",disc);
            flag = 1;
            break;
        case 'N':
        case 'n':
            flag = 1;
            break;
        default:
            printf("Invalid input!\n");
            break;
        }
    }

    fprintf(fbill,"\n---------------------------------------\n");
    fprintf(fbill,"\nPrice:                        %.2f",sum);
    vat = sum * 18 / 100;
    sum = sum + vat; //VAT value calculated before student discount, and added to price payable.
    fprintf(fbill,"\nPrice + VAT:                  %.2f\n",sum);

    fclose(fbill);
    return 0;
}



int billing(){
    fbill = fopen("bill.txt","w");
    fprintf(fbill,"210104004055           ");
    time_t t;
    t = time(NULL);
    char arr[30];
    strftime(arr,sizeof(arr),"%d.%m.%Y/%H:%M",localtime(&t));
    fprintf(fbill,"%s",arr);
    fprintf(fbill,"\n---------------------------------------\n");
    fprintf(fbill,"Product                       Price\n");
    fprintf(fbill,"---------------------------------------");
    fprintf(fbill,"\n");
    fclose(fbill);
    float sum = 0;
    float price;
    int c,i,servings;
    while(1){
        int boslukcu = 1;
        int choose = 99;
        while (choose < 1 || choose > 10){
            printf("\nPlease choose a product (1-10): ");
            scanf("%d",&choose);
            choose += 2;
            if((choose < 1 || choose > 10)){
                printf("Please enter a valid selection!!\n");
            }
            getchar();
        }

        printf("\n");
        while(1){
            printf("How many servings do you want?: ");
            scanf("%d",&servings);
            break;
            
        }

        if(servings != 0){
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
            sum += price;
            for(i = 0; i < 30 - boslukcu ;i++){
                fprintf(fbill," ");
            }
            fprintf(fbill,"%.2f\n",price);
            fclose(fbill);
        }
        else{
            total(sum);
            billtoterminal();
            //fprintf(fbill,"%.2f",total(student,sum));
            return 0;
        }
    }
    
    return 1;
}



int menuing(){
    fmenu = fopen("menu.txt","r");
    int i = 1,k = 0;
    printf("Yemek Listesi:\n");
    printf("1. ");

    while(1){
        int c = fgetc(fmenu);

        if(c == EOF){
            printf("\n");
            return 0;
        }
        if(((c >= 48 && c <= 57) || c == 46) || k < 2){}
        else{
            printf("%c",c);
        }
        if(c == 10){
            k++;
            if(k > 2){
                i++;
                printf("%d. ",i);
            }
        }
    }

    fclose(fmenu);

    printf("\n\n");
    return 0;
}