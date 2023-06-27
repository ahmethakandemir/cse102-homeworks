#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[50];
    int age;
    struct Node* mother;
    struct Node* father;
};



int search_tree(struct Node* root, char* name) {
    // If the root is null, return 0 (not found)
    if (root == NULL) {
        return 0;
    }
    
    // If the searched name is found in the root node, return 1 (found)
    if (strcmp(root->name, name) == 0) {
        return 1;
    }
    
    // If the searched name is less than the current node's name, search in the left subtree
    if (strcmp(root->name, name) > 0) {
        return search_tree(root->mother, name);
    }
    
    // Otherwise, search in the right subtree
    return search_tree(root->father, name);
}

void addNode(struct Node ** currentNode){

    struct Node * box = (struct Node*)malloc(sizeof(struct Node));
    char tempmom[50];
    char tempdad[50];
    
    printf("enter name of the person: ");
    scanf("%s",box->name);
    printf("enter age of the person: ");
    scanf("%d",&box->age);
    if(*currentNode == NULL){
        box->father = NULL;
        box->mother = NULL;
        *currentNode = box; 
        return;
    }
    else{
        printf("enter mother's name of the person: ");
        scanf("%s",tempmom);
        if(search_tree(*currentNode,tempmom)){
            printf("enter father's name of the person: ");
            scanf("%s",tempdad);
            if(search_tree(*currentNode,tempdad)){
                // Find the mother and father nodes
                struct Node * mother = NULL;
                struct Node * father = NULL;
                while ((*currentNode)->mother != NULL && (*currentNode)->father != NULL) {
                    if (strcmp((*currentNode)->name, tempmom) == 0) {
                        mother = (*currentNode);
                    }
                    if (strcmp((*currentNode)->name, tempdad) == 0) {
                        father = (*currentNode);
                    }
                    (*currentNode) = (*currentNode)->father;
                }

                // Assign the mother and father pointers to the box node's mother and father pointers
                box->mother = mother;
                box->father = father;

                // Assign the box node as the child of the mother and father nodes
                mother->father = box;
                father->mother = box;
            }
        }
    }
}

void print_tree(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    
    // Print the node's information with appropriate indentation
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s (%d)\n", root->name, root->age);
    
    // Traverse the left sub-tree (mother node)
    print_tree(root->mother, level + 1);

    // Traverse the right sub-tree (father node)
    print_tree(root->father, level + 1);
}


int main(){

    int sentinel;
    struct Node * f1 = NULL;
    while(sentinel != -1){
        addNode(&f1);
        printf("enter sentinel: ");
        scanf("%d",&sentinel);
    }
    
    print_tree(f1,5);


    return 0;
}