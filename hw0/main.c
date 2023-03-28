#include <stdio.h>
#include "util.h"


int main() {

    int num1,num2,den1,den2;
    // Getting numbers to operate..
    printf("Enter first number's nominator: ");
    scanf("%d",&num1);
    
    printf("Enter first number's denominator: ");
    scanf("%d",&den1);
    
    printf("Enter second number's nominator: ");
    scanf("%d",&num2);

    printf("Enter second number's denominator: ");
    scanf("%d",&den2);
    
    // The denominator can't be equal to 0, so we need to check if a denominator is equal to 0..
    if(den1 == 0 || den2 == 0){
        printf("Invalid entry for denominator!!!\n");
        return 0;
    }
    
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    
    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    
    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    return(0);
}
