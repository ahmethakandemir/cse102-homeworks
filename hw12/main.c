#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
}Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
}Asset4;

void fillLinkedList(struct Node** head) {
    struct timeval time;
    gettimeofday(&time, NULL);

    int assetCount = (time.tv_usec % 11) + 10;
    int i;

    for (i = 0; i < assetCount; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

        int assetType = (time.tv_sec + getpid() + i) % 4 + 1;

        switch (assetType) {
            case 1: {
                Asset1* newAsset1 = (Asset1*)malloc(sizeof(Asset1));
                strcpy(newAsset1->type, "asset1");
                newAsset1->ivals[0] = rand();
                newAsset1->svals[0] = ((double)rand() / RAND_MAX);
                newNode->data = newAsset1;
                break;
            }
            case 2: {
                Asset2* newAsset2 = (Asset2*)malloc(sizeof(Asset2));
                strcpy(newAsset2->type, "asset2");
                newAsset2->ivals[0] = rand();
                newAsset2->ivals[1] = rand();
                newAsset2->svals[0] = ((double)rand() / RAND_MAX);
                newAsset2->svals[1] = ((double)rand() / RAND_MAX);
                newNode->data = newAsset2;
                break;
            }
            case 3: {
                // Handle Asset3 initialization
                Asset3* newAsset3 = (Asset3*)malloc(sizeof(Asset3));
                strcpy(newAsset3->type, "asset3");
                strcpy(newAsset3->string1, "Example String 1");
                strcpy(newAsset3->string2, "Example String 2");
                newNode->data = newAsset3;
                break;
            }
            case 4: {
                // Handle Asset4 initialization
                Asset4* newAsset4 = (Asset4*)malloc(sizeof(Asset4));
                strcpy(newAsset4->type, "asset4");
                newAsset4->value1 = ((double)rand() / RAND_MAX);
                newAsset4->value2 = ((float)rand() / RAND_MAX);
                newAsset4->value3 = ((double)rand() / RAND_MAX);
                newNode->data = newAsset4;
                break;
            }
            default:
                // Handle unrecognized asset types or error cases
                printf("Unknown asset type.\n");
                free(newNode);
                continue;
        }

        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}


void printLinkedList(struct Node* head) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(((Asset1*)current->data)->type, "asset1") == 0) {
            Asset1* asset = (Asset1*)current->data;
            printf("\nType: %s\n", asset->type);
            printf("Integer Value: %d\n", asset->ivals[0]);
            printf("Double Value: %lf\n", asset->svals[0]);
        } else if (strcmp(((Asset2*)current->data)->type, "asset2") == 0) {
            Asset2* asset = (Asset2*)current->data;
            printf("\nType: %s\n", asset->type);
            printf("Integer Values: %d, %d\n", asset->ivals[0], asset->ivals[1]);
            printf("Double Values: %lf, %lf\n", asset->svals[0], asset->svals[1]);
        } else if (strcmp(((Asset3*)current->data)->type, "asset3") == 0) {
            Asset3* asset = (Asset3*)current->data;
            printf("\nType: %s\n", asset->type);
            printf("String 1: %s\n", asset->string1);
            printf("String 2: %s\n", asset->string2);
        } else if (strcmp(((Asset4*)current->data)->type, "asset4") == 0) {
            Asset4* asset = (Asset4*)current->data;
            printf("\nType: %s\n", asset->type);
            printf("Value 1: %lf\n", asset->value1);
            printf("Value 2: %f\n", asset->value2);
            printf("Value 3: %lf\n", asset->value3);
        } else {
            printf("Unknown asset type.\n");
        }

        current = current->next;
    }
}


int main() {
    struct Node* head = NULL;
    fillLinkedList(&head);
    printLinkedList(head);
    return 0;
}
