#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int menuing();
int billing();
float total(float sum);
void billtoterminal();
int rps();

FILE * fmenu;
FILE * fbill;

int main(){
    menuing();
    billing();
    rps();
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
    float stddisc,yuzellidisc;
    int flag = 0;
    float vat;
    fbill = fopen("bill.txt","a");
    fprintf(fbill,"\nTotal:                        %.2f",sum);

    while(!flag){

        printf("Are you student? (Y/N):");
        scanf(" %c",&student);
        switch (student)
        {
        case 'y':
        case 'Y':
            stddisc = sum * 12.5 / 100;
            sum -= stddisc;
            fprintf(fbill,"\nStudent Discount:            -%.2f",stddisc);

            flag = 1;
            break;
        case 'N':
        case 'n':
            if(sum >=150){
                yuzellidisc = sum * 0.1;
                fprintf(fbill,"\n%%10 discount:                -%.2f",yuzellidisc);
                sum -= yuzellidisc;
            }
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
    fprintf(fbill,"\n---------------------------------------\n");
    
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
            
            if((scanf("%d",&servings) == 1)){
                break;
            }
            printf("Please enter a valid number!!\n\n");
            getchar();
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
                if(servings >= 1000){
                    boslukcu += 6;
                }
                else if(servings >= 100){
                    boslukcu += 5;
                }
                else if(servings >= 10){
                    boslukcu += 4;
                }
                else{
                    boslukcu += 3;
                }
                fprintf(fbill,"%d* ",servings);
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

int rps(){
    srand(time(NULL));
    
    int comp,user;
    #define stone 1
    #define paper 2
    #define scissors 4

    comp = rand()%3 + 1;
    if(comp == 3){
        comp++;
    }

    printf("Please make a choice!\n""1: Stone, 2: Paper, 3: Scissors\n");
    while(1){
        if((scanf("%d",&user) == 1) && ((user <= 3) && user >= 1)){
            if(user == 3){
                user++;
            }
            break;
        }
        else{
            printf("\ninvalid selection!!\n");
        }
    }
    
    if(user == stone){
        printf("You chose Stone. ");
    }
    else if(user == paper){
        printf("You chose Paper. ");
    }
    else{
        printf("You chose Scissors. ");
    }
    if(comp == stone){
        printf("I chose Stone. ");
    }
    else if(comp == paper){
        printf("I chose Paper. ");
    }
    else{
        printf("I chose Scissors. ");
    }
    if(user == comp){
        printf("It's a tie!\n");
    }
    else if((user * 2 == comp) || (comp * 4 == user)){
        printf("I won!\n");
    }
    else{
        printf("You won!\n");
    }
    char again;
    int flag = 1;
    while (flag == 1)
        {
        printf("Do you want to play again?? ");
        scanf(" %c",&again);
        switch (again)
        {
        case 'Y':
        case 'y':
            rps();
            flag = 0;
            break;
        case 'N':
        case 'n':
            printf("Good bye!!");
            return 0;
        default:
            printf("Invalid selection!\n");
            break;
        }
    }

    return 0;
}