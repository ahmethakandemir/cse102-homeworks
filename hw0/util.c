#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    // If the numerator equals to 0, that means this fractional number equals to 0, so no need to print "//" between nominator and denominator. 
    if(numerator == 0){
        printf("0");
    }
    // If numerator and denominator are equal, the result will be 1, so no need to print "1//1".
    else if(numerator == denominator){
        printf("1");
    }
    // If numerator equals to denominator * -1, the result will be -1, so no need to print "-1//1".
    else if (numerator == denominator*-1)
    {
        printf("-1");
    }
    
    else{
        printf("%d//%d", numerator, denominator);
    }
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);

} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);


} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {

    *n3 = n1*d2;
    *d3 = d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    // Checking if nominator or denominator is negative, if negative, temporarly made it positive for correct calculations.
    int nchecker = 0;
    int dchecker = 0;
    if(*n < 0){
        *n *= -1; 
        nchecker = 1;
    }
    if(*d < 0){
        *d *= -1; 
        dchecker = 1;
    }
    
    // To find the GCD, we defined a temp value to storage the greatest common divisor, in order to divide numerator and denominator to that temp value.
    int max_value;
    max_value = 1;
    for(int i = 1;i <= *n && i <= *d;i++){
        if ((*n % i == 0) && (*d % i == 0)){
            max_value = i;
            
        }
    }
    // If nominator or denominator is negative, as we said in line 54, we are turning the value negative again.  
    if (nchecker){
        *n = (*n / max_value)*-1;
    }
    else
        *n = *n / max_value;

    if (dchecker){
        *d = (*d / max_value)*-1; 
    }
    else    
        *d = *d / max_value; 

} 

/* end fraction_div */
