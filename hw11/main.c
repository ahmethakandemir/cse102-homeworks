#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    
    int num;
    struct node* next;
    
}newtype;


void fillfifo(newtype ** head){

    int input = 1;
    newtype * temp;

    while (1){
        printf("enter your number;");
        scanf("%d",&input);
        if(input == 0){
            break;
        }
        newtype * kutu = (newtype*)malloc(sizeof(newtype));
        kutu->num = input;
        kutu->next = NULL;
        if(*head == NULL){
            *head = kutu;
        }
        else{
            temp=*head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = kutu;
        }

    }
}

void filllifo(newtype ** head){

    int input = 1;
    newtype * temp;


    while (1){
        printf("enter your number;");
        scanf("%d",&input);
        if(input == 0){
            break;
        }
        newtype * kutu = (newtype*)malloc(sizeof(newtype));
        kutu->num = input;
        kutu->next = NULL;
        if(*head == NULL){
            *head = kutu;
        }
        else{
            temp = kutu;
            temp->next = *head;
            *head = temp;
        }
    }
}

void prt(newtype * head){
    newtype *temp = head;

    while(temp != NULL){
        printf("%d\n",temp->num);
        temp = temp->next;
    }


}
/*KUTU*/
/*   num = 4; next = NULL*/
/*head*/
/*   num = 5; next = NULL*/
/*temp*/
/*   num = 4; next = *head*/


int main(){
    newtype * head = NULL;
    filllifo(&head);
    prt(head);
    return 0;
}