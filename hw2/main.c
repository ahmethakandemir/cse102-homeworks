#include <stdio.h>
#include <math.h>

int calculator();
void leap();
void grades();

int main(){
    //leap();
    //grades();
    calculator();
}

int calculator(){
    printf("\n**********************************************\n");
    char output,operation;
    int m,n;
    double final;
    double a,b;
    
    int c = 0;
    while(c == 0){
        while(1){
            printf("\nenter the format of output (S or I): ");
            scanf("%s",&output);
            if (output == 'S' || output == 's' || output == 'I' || output == 'i'){
                c = 1;
                break;
            }
        }
    
        while (output == 'S' || output == 's'){
            printf("\nenter m and n values: ");
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
    printf("Enter the operation(+,-,/,*,%%,!,^): ");
    scanf(" %c",&operation);

    if(operation == '!'){
        printf("Enter the operand: ");
        scanf("%lf",&a);
    }
    else{
        printf("Enter the first operand: ");
        scanf("%lf",&a);
        printf("Enter the second operand: ");
        scanf("%lf",&b);
    }
    
    int inta,intb;
    inta = a;
    intb = b;
    
    switch (operation)
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
        return 0;
    }

    int intfinal = final;
    // output turu I oldugunda finali yazdirdigimiz kisim..
    if(output == 'I' || output == 'i'){
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
    // bilimsel sekilde yazdirdigimiz kisim,,
    if(output == 'S' || output == 's'){
        if(operation != '!'){
            printf("%.2f %c %.2f = ", a, operation, b);
        }
        else{
            printf("%d! = ", inta); 
        }
            int soltaraf = m - n;
            // intfinal in eleman sayisini hesaplamaliyim ki tamfinaldigitten cikarabileyim, ve sayinin xxxxx formatini tam m ile ayni sayida tutabileyim
            int intfinaldigit = 0;
            if(intfinal != 0){
                while (intfinal != 0){
                    intfinaldigit++;
                    intfinal /= 10;
                }
            }
            else{
                intfinaldigit = 1;
            }

            int tamfinal;//tamfinal degeri, final degerinin xx,xxx seklindeki formatinin xxxxx sekline sokulmus halidir.
            int tamlamacarpani = 1;
            for(int i = 0; i < m - intfinaldigit;i++){
                tamlamacarpani *= 10;
            }
            tamfinal = final * tamlamacarpani;// su an tamfinal degerimiz virgulsuz formatta,int olarak tanimladik, basamak sayisini bulup yazdirma islemine calisicaz.
            int tamtemp = tamfinal;// variable karisikligini onlemek icin tamfinalle islem yaptiktan sonra surekli bu degere esitleyecegim. cunku pointer kullanamayacak kadar cahil ve zavalliyim.
            int virgulleme = 1;
            for(int i = 0; i < n;i++){
                virgulleme *= 10;
            }
            //xxxx.x0
            int soltamfinal;// tam finalin soldaki degeri..
            soltamfinal = tamfinal / virgulleme;
            
            int soltamfinaltemp = soltamfinal;
            int soltamfinaldigit = 0;
            
            if(soltamfinal != 0){
                while (soltamfinal != 0){
                    soltamfinaldigit++;
                    soltamfinal /= 10;
                }
            }
            else{
                soltamfinaldigit = 1;
            }
            int soltamfinaldigittemp = soltamfinaldigit;
            
            soltamfinal = soltamfinaltemp;
            int ekleme = 1;
            for(int i = soltaraf; soltaraf < soltamfinaldigit; i++){
                soltamfinaldigit--;
                soltamfinal /= 10;
                virgulleme *= 10;
                ekleme *= 10;
            }  
            if(soltamfinaldigit != soltaraf){
                for(int i = soltamfinaldigit; i < soltaraf;i++);
                printf("0");
                
            }

            printf("%d.",soltamfinal);

            int sagtamfinal;
            sagtamfinal = tamfinal % virgulleme;
//          virgulun saginin basamak sayisini bulmaliyim cunku 074 yazdirmak isterken 74 yazdirmak istemem..
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
//          burda da '0' i yazdirma isini yapiyoruz. eksik kalan 0 lari yazdirmis oluyoruz.
            if(n != sagtamfinaldigit){
                for(int i = 0;i < n - sagtamfinaldigit;i++){
                    printf("0");
                }
            }

            printf("%d",sagtamfinal/ekleme);
            printf("e%d",intfinaldigit - soltaraf);
            printf("\n");
            printf("**********************************************\n");
            return 0;
    }
}
void leap(){
    int year;
    printf("\n**********************************************\n");
    printf("enter the year: ");
    scanf("%d",&year);

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
    printf("\n**********************************************\n");
}

void grades(){
    printf("\n**********************************************\n");
    int e1,e2,e3,a1,a2;
    printf("enter the exam grades: ");
    scanf("%d%d%d",&e1,&e2,&e3);
    printf("enter the assigments grades: ");
    scanf("%d%d",&a1,&a2);

    float final;
    final = ((e1 + e2 + e3)/3 * 0.6) + ((a1 + a2) /2 * 0.4);

    if(final < 60){
        printf("Final grade: %.1f Failed!",final);
    }
    else{
        printf("Final grade: %.1f Passed!",final);
    }
    printf("\n**********************************************\n");
}



