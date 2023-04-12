#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int menuing();
int billing();
float total(float sum);
void billtoterminal();
int rps();

FILE * fmenu; // open the menu file
FILE * fbill; // open the file which will be our bill file.

int main(){
    //menuing();
    //billing();
    rps(); // rock paper scissors.
}
int menuing(){  // printinh the menu function
    fmenu = fopen("menu.txt","r");
    int i = 1,k = 0; // k is our line num, in menu file the first 2 line is trash so we need to skip them somehow.
    printf("Yemek Listesi:\n");
    printf("1. ");

    while(1){ // a while loop which will last until reaching EOF
        int c = fgetc(fmenu);

        if(c == EOF){
            printf("\n");
            return 0;
        }
        if(((c >= 48 && c <= 57) || c == 46) || k < 2){} // here if our character is digit or a space, we are ignoring it and do nothing.
        else{
            printf("%c",c); // else we are printing it and that means we only print the meal name on the menu.
        }
        if(c == 10){
            k++;
            if(k > 2){
                i++;
                printf("%d. ",i); // printing 1. 2. at the beginning of product names.
            }
        }
    }

    fclose(fmenu);

    printf("\n\n");
    return 0;
}






int billing(){  // printing the bill.
    fbill = fopen("bill.txt","w");
    fprintf(fbill,"210104004055           ");

    time_t t;
    t = time(NULL);
    char arr[30]; // I needed to use an array to use strftime because you said use this function, so i can't do it without it as you know.
    strftime(arr,sizeof(arr),"%d.%m.%Y/%H:%M",localtime(&t));
    fprintf(fbill,"%s",arr);
    
    fprintf(fbill,"\n---------------------------------------\n");
    fprintf(fbill,"Product                       Price\n");
    fprintf(fbill,"---------------------------------------");
    fprintf(fbill,"\n");
    fclose(fbill);
    float sum = 0; // used to calculate total price of products.
    float price; // and this is the final price 
    int c,i,servings;
    while(1){ // this while loop is for printing the selection to the bill until 0 is pressed.
        int boslukcu = 1; // i used this variable to arrange spaces in bill to make it look less messy.
        int choose = 99; // this can be anything except 1,12.
        while (choose < 1 || choose > 12){  // prompt until user enters a valid value.
            printf("\nPlease choose a product (1-12): ");
            scanf("%d",&choose);
            if((choose < 1 || choose > 12)){
                printf("Please enter a valid selection!!\n");
            }
            getchar();
        }
        choose += 2; // ignoring the first 2 trash line

        printf("\n");
        while(1){ // same as choose thing, prompt until user enters a valid value.
            printf("How many servings do you want?: ");
            
            if((scanf("%d",&servings) == 1)){ // checking if input is integer.
                break;
            }
            printf("Please enter a valid number!!\n\n");
            getchar();
        }

        if(servings != 0){  // if 0 is not inputted for serving count,,
            fbill = fopen("bill.txt","a+");
            fmenu = fopen("menu.txt","r");
            for(i = 0; i < choose - 1;i++){ // here, it looks like an empty loop but i used it to go to exact line i want, the chosen meals line.
                while ((c = fgetc(fmenu)) != EOF){
                    if(c == 10){
                        break;  // breaks every new line and does this for chosen number times.
                    }
                }
            }

            if(servings > 1){ // it is for arranging spaces so not that important i guess.
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

            while ((c = fgetc(fmenu)) != 32){ // printing the name on the bill
                fprintf(fbill, "%c",c);
                boslukcu++; // arranging spaces.
            }

            fprintf(fbill," ");
            
            fscanf(fmenu,"%f",&price); // getting the price.
            
            fclose(fmenu);

            price *= servings; // multiplying price with serving counts.
            sum += price;       // adding all of items on the bill to one total.
            for(i = 0; i < 30 - boslukcu ;i++){ // printing the arranged spaces.
                fprintf(fbill," ");
            }
            fprintf(fbill,"%.2f\n",price); // printing the price.
            fclose(fbill);
        }
        else{   // 0 is entered as servings count.
            total(sum);     // running the total func.
            billtoterminal();// printing the bill.txt to terminal.
            return 0;
        }
    }
    
    return 1;
}

float total(float sum){
    char student;
    float stddisc = 0,yuzellidisc;
    int flag = 0;
    float vat;
    fbill = fopen("bill.txt","a");
    fprintf(fbill,"\nTotal:                        %.2f",sum); // total price without VAT or discounts.

    while(!flag){ // asking if student until a valid answer.

        printf("Are you student? (Y/N):");
        scanf(" %c",&student);
        switch (student)
        {
        case 'y':
        case 'Y': // if student, calculating the discount and printing it. 
            stddisc = sum * 12.5 / 100;
            
            fprintf(fbill,"\nStudent Discount:            -%.2f",stddisc);

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
    if(sum >=150){ // if the total is above 150 tl, discount will be applied.
        yuzellidisc = sum * 0.1;
        fprintf(fbill,"\n%%10 discount:                -%.2f",yuzellidisc); // and printing the discounted value.
        sum -= yuzellidisc; 
    }
    sum -= stddisc; // discountings...
    fprintf(fbill,"\n---------------------------------------\n");
    fprintf(fbill,"\nPrice:                        %.2f",sum);
    vat = sum * 18 / 100;
    sum = sum + vat; //VAT value calculated and added and printed.
    fprintf(fbill,"\nPrice + VAT:                  %.2f\n",sum);
    printf("\n---------------------------------------\n");
    
    fclose(fbill);
    return 0;
}

void billtoterminal(){ // an infinitive loop which will last until EOF, printing the bill.txt to terminal.
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



int rps(){ // rock paper scissors.
    srand(time(NULL));
    
    int comp,user;
    #define stone 1
    #define paper 2
    #define scissors 4 // it is 4 because i can make calculations like if (a == 2 * b), a wins. it wasnt necessary but i thought like this and now i don't have time to change it.

    comp = rand()%3 + 1; // random value generating.
    if(comp == 3){
        comp++;
    }

    printf("Please make a choice!\n""1: Stone, 2: Paper, 3: Scissors\n"); // asking until a valid answer.
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
    // simple printings.
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
    else if((user * 2 == comp) || (comp * 4 == user)){ // deciding who won.
        printf("I won!\n");
    }
    else{
        printf("You won!\n");
    }
    char again;
    int flag = 1;
    while (flag == 1) // prompting until user doesn't want to play anymore.
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