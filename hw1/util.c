#include <stdio.h>
#include "util.h"


int takeGCD(int first,int second,int temp,int tempvalue,int counter){
    counter++;
    // counter is basically just used to print the things below only once, because takeGCD() is a recursive function..
    if(counter == 1){
        printf("Taking the GCD operation....\n--------------------------\n");
        printf("First number: ");
        scanf("%d",&first);
        printf("Second number: ");
        scanf("%d",&second);
    }

    // arranging first and second in an order..
    if (second > first){
    temp = first;
    first = second;
    second = temp;
}
    // started to apply euclidian algorithm recursively..
    tempvalue = first % second;
    
    if (tempvalue == 0){
        printf("GCD is: %d\n=========================\n",second);
        return(0);
    }
    else{
        first = second;
        second = tempvalue;
        
        takeGCD(first,second,temp,tempvalue,counter);
    }

}


int takeSum(){
    
    int first,second,result;
    // it is basically just math and some printf functions.
    printf("Taking the sum operation....\n--------------------------\n");
    printf("First number: ");
    scanf("%d",&first);
    printf("Second number: ");
    scanf("%d",&second);
    
    result = first + second;
    printf("Result: \n");
    printf("%7d\n",first);    
    printf("%7d\n",second);
    printf("+\n");
    printf("-------\n");
    printf("%7d\n",result);
    printf("\n=========================\n");
}


int takeMultiply(){

    int first,second;
    printf("Multiplying operation....\n--------------------------\n");
    printf("First number: ");
    scanf("%d",&first);
    printf("Second number: ");
    scanf("%d",&second);

    int tempvalue,sum,check,checksec,checkfirst,value;

    // arranging second and first in an order which first is bigger than second..
    if(second > first){
        int temp;
        temp = first;
        first = second;
        second = temp;
    }
    tempvalue = second;

    // calculating first number's digit count..
    checkfirst = first;
    check = 0;
    while (checkfirst != 0){

        checkfirst /= 10;
        check++;
    }
    checkfirst = check;

    
    // calculating digit count of second number..
    checksec = second;
    check = 0;
    while (checksec != 0){

        checksec /= 10;
        check++;
    }
    checksec = check;

    // printing the casuals..
    printf("%10d\n",first);
    printf("%10d\n",second);
    printf("*\n");
    printf("----------\n");



    for(int i = 1; i <= checksec; i++){
            // k is the indent value to print the multiplication as if it has calculated on a paper..
            int k = 11 - i;
            value = second % 10;
            second /= 10;
            if (value == 0){
                printf("%*s",(k - checkfirst)," ");
                for(int m = 0;m < checkfirst;m++){
                    printf("0");
                }
                printf("\n");
            }
            else
            {
            printf("%*d\n",k, value * first);
            }
    }

    printf("+\n----------\n");
    printf("%10d\n",first * tempvalue);
    printf("\n=========================\n");
}



int take5(){
    int first;
    printf("Comparing according to 5 operation....\n--------------------------\n");
    printf("Enter the number: ");
    scanf("%d",&first);

    if((first <= 5) && (first > 0)){
        printf("The integer you entered is less than or equal to 5 \n");
    }
    else if ((first <= 10) && (first > 5)){
        printf("The integer you entered is greater than 5 \n");
    }
    else {
        printf("Invalid input\n");
    }
    printf("\n=========================\n");
}
