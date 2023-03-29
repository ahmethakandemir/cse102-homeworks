#include <stdio.h>
#include <math.h>

int calculator();
int leap();
int grades();

int main(){
    
    leap();
    calculator();
    grades();
    
}

int calculator(){
    
    char output,operation;
    int m,n;
    double final;
    double a,b;
    
    int c = 0; // c is just used to check and reprompt the user if n > m situation occurs.
    while(c == 0){ // this loop will continue asking output format or m and n values until it gets valid answers from user. 
        while(1){ // this loop is for output format.
            printf("\nenter the format of output (S or I): ");
            scanf(" %c",&output);
            if (output == 'S' || output == 's' || output == 'I' || output == 'i'){
                c = 1;
                break;
            }

        }
    
        while (output == 'S' || output == 's'){ // this loop is when user enters S for output format, prompts m and n values until a valid answer.
            printf("enter m and n values: ");
            scanf("%d%d",&m,&n);

            if(n >= m){
                printf("n value can't be equal to or greater than m value!!\nReprompt..\n");
            }
            else{
                c = 1;
                break;
            }
        }

    }
    printf("Enter the operation(+,-,/,*,%%,!,^): ");// getting the operation from user.
    scanf(" %c",&operation);

    if(operation == '!'){ // when the operation is '!', there will be only one operand, so i needed to print it seperately.
        printf("Enter the operand: ");
        scanf("%lf",&a);
    }
    else{   // taking the operands
        printf("Enter the first operand: ");
        scanf("%lf",&a);
        printf("Enter the second operand: ");
        scanf("%lf",&b);
    }
    
    int inta,intb; // needed to take int values of inputs in order to calculate factorial and module operations.
    inta = a;
    intb = b;
    
    switch (operation) // making the calculations
    {
    case '+':
        final = a + b;
        break;
    case '-':
        final = a - b;
        break;
    case '*':
        final = a * b;
        break;
    case '/':
        final = a / b;
        break;
    case '%':
        final = inta % intb;
        break;
    case '^':
        final = pow(a,b);
        break;
    case '!':
        int k = 1,temp;
        temp = inta;
        while(temp > 1){
            k = k * temp;
            temp--;   
        }
        final = k;
        break;
    default:
        printf("\nInvalid input for operation!!!!!\n");
        printf("**********************************************\n\n");
        return 0;
    }

    int intfinal = final; // we will need just left side of final value, so i am getting it with typecasting.
    
    if(output == 'I' || output == 'i'){ // this is where we print the result when output format is I..
        if(operation != '!'){
            printf("%d %c %d = %d\n", inta, operation, intb, intfinal);
            return 0;
        }
        else{
            printf("%d! = %d\n", inta, intfinal);
            printf("\n");
            return 0;
        }
    }

    if(output == 'S' || output == 's'){// this is where we print the result when the output format is S..
        if(operation != '!'){
            printf("%.2f %c %.2f = ", a, operation, b);
        }
        else{
            printf("%d! = ", inta); 
        }
            int soltaraf = m - n; // this is just to prevent variable mess.
             
            int intfinaldigit = 0; // calculating intfinaldigit value in order to changing the format of xx.xxx , to xxxxx; and printing 'e' value.
            if(intfinal != 0){     
                while (intfinal != 0){
                    intfinaldigit++;
                    intfinal /= 10;
                }
            }
            else{
                intfinaldigit = 1;
            }

            int tamfinal;//tamfinal value is final value but floating point added to int point, xxxxx format will be created.
            int tamlamacarpani = 1;
            for(int i = 0; i < m - intfinaldigit;i++){
                tamlamacarpani *= 10;
            }
            tamfinal = final * tamlamacarpani;// with tamlamacarpani value, we will be able to make the tamfinal value's digit count equal to m value, if m = 7, our xxxxx value will be xxxxx00.
            int tamtemp = tamfinal;// tamtemp is used to storage tamfinal value after calculations.
            int virgulleme = 1; // virgulleme is used to multiply with 10^n to format the number as given in m and n.
            for(int i = 0; i < n;i++){
                virgulleme *= 10;
            }
            
            int soltamfinal;// we will create a soltamfinal value which is final value's before '.'
            soltamfinal = tamfinal / virgulleme;
            
            int soltamfinaltemp = soltamfinal;
            int soltamfinaldigit = 0;// this is soltamfinal's digit count.
            
            if(soltamfinal != 0){
                while (soltamfinal != 0){
                    soltamfinaldigit++;
                    soltamfinal /= 10;
                }
            }
            else{
                soltamfinaldigit = 1;
            }
            int soltamfinaldigittemp = soltamfinaldigit; //this is used to storage the value after calculations.
            
            soltamfinal = soltamfinaltemp;
            int ekleme = 1; // this part is used for the situations when the final value has more digits than m value.
            for(int i = soltaraf; soltaraf < soltamfinaldigit; i++){
                soltamfinaldigit--;
                soltamfinal /= 10;
                virgulleme *= 10;
                ekleme *= 10;
            }  
            if(soltamfinaldigit != soltaraf){ // when soltaraf value is more than final value, in order to there will not be missing digit, we are printing '0's.
                for(int i = soltamfinaldigit; i < soltaraf;i++);
                printf("0");
            }

            printf("%d.",soltamfinal); // printing final values left side.

            int sagtamfinal;
            sagtamfinal = tamfinal % virgulleme;// this part is also used for printing zero's but to the right side of dot when digit nums is not equal. here it calculates digit num of right side.
//          
            int sagtamfinaltemp = sagtamfinal;
            int sagtamfinaldigit = 0;
            
            if(sagtamfinal != 0){
                while (sagtamfinal != 0){
                    sagtamfinaldigit++;
                    sagtamfinal /= 10;
                }
            }
            else{
                sagtamfinaldigit = 1;
            }
            sagtamfinal = sagtamfinaltemp;
            if(n != sagtamfinaldigit){ // this is where we print '0's.
                for(int i = 0;i < n - sagtamfinaldigit;i++){
                    printf("0");
                }
            }
            // printing the final value and e value.
            printf("%d",sagtamfinal/ekleme);
            printf("e%d",intfinaldigit - soltaraf);
            printf("\n\n");
            printf("**********************************************\n\n");
            return 0;
    }
}
int leap(){
    int year;
    printf("\n**********************************************\n");
    printf("enter the year: ");
    scanf("%d",&year);
    // we are taking year value and checking if it is leap or not.
    if(year % 400 == 0){
        printf("%d is a leap year.\n",year);
    }
    else if (year % 100 == 0)
    {
        printf("%d is not a leap year.\n",year);
    }
    else if (year % 4 == 0){
        printf("%d is a leap year.\n",year);
    }
    else{
        printf("%d is not a leap year.\n",year);
    }
    printf("\n\n**********************************************\n\n");
    return 0;
}

int grades(){
    
    int e1,e2,e3,a1,a2;
    printf("enter the exam grades(between 0-100): ");
    scanf("%d%d%d",&e1,&e2,&e3);
    printf("enter the assigments grades(between 0-100): ");
    scanf("%d%d",&a1,&a2);

    float final; // this is result value.
    final = ((e1 + e2 + e3)/3 * 0.6) + ((a1 + a2) /2 * 0.4);

    if(final < 60){
        printf("Final grade: %.1f Failed!",final);
    }
    else{
        printf("Final grade: %.1f Passed!",final);
    }
    printf("\n\n**********************************************\n");
    return 0;
}



