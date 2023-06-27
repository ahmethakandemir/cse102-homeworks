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

void serializeLinkedList(struct Node* head) {
    Node* current = head;
    FILE* file = fopen("linkedlist.bin", "wb");

    while (current != NULL) {
        if (strcmp(((Asset1*)current->data)->type, "asset1") == 0) {
            Asset1* asset = (Asset1*)current->data;
            fwrite(asset->type, sizeof(asset->type), 1, file);
            fwrite(asset->ivals, sizeof(asset->ivals), 1, file);
            fwrite(asset->svals, sizeof(asset->svals), 1, file);
        } else if (strcmp(((Asset2*)current->data)->type, "asset2") == 0) {
            Asset2* asset = (Asset2*)current->data;
            fwrite(asset->type, sizeof(asset->type), 1, file);
            fwrite(asset->svals, sizeof(asset->svals), 1, file);
            fwrite(asset->ivals, sizeof(asset->ivals), 1, file);
        } else if (strcmp(((Asset3*)current->data)->type, "asset3") == 0) {
            Asset3* asset = (Asset3*)current->data;
            fwrite(asset->type, sizeof(asset->type), 1, file);
            fwrite(asset->string1, sizeof(asset->string1), 1, file);
            fwrite(asset->string2, sizeof(asset->string2), 1, file);
        } else if (strcmp(((Asset4*)current->data)->type, "asset4") == 0) {
            Asset4* asset = (Asset4*)current->data;
            fwrite(asset->type, sizeof(asset->type), 1, file);
            fwrite(&asset->value1, sizeof(asset->value1), 1, file);
            fwrite(&asset->value2, sizeof(asset->value2), 1, file);
            fwrite(&asset->value3, sizeof(asset->value3), 1, file);
        } else {
            printf("Unknown asset type.\n");
        }

        current = current->next;
    }

    fclose(file);
}


void deserializeLinkedList(struct Node** head) {
    FILE* file = fopen("linkedlist.bin", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (!feof(file)) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

        // Read the type of the asset
        char assetType[20];
        fread(assetType, sizeof(assetType), 1, file);

        if (strcmp(assetType, "asset1") == 0) {
            Asset1* newAsset1 = (Asset1*)malloc(sizeof(Asset1));
            fread(newAsset1->type, sizeof(newAsset1->type), 1, file);
            fread(newAsset1->ivals, sizeof(newAsset1->ivals), 1, file);
            fread(newAsset1->svals, sizeof(newAsset1->svals), 1, file);
            newNode->data = newAsset1;
        } else if (strcmp(assetType, "asset2") == 0) {
            Asset2* newAsset2 = (Asset2*)malloc(sizeof(Asset2));
            fread(newAsset2->type, sizeof(newAsset2->type), 1, file);
            fread(newAsset2->svals, sizeof(newAsset2->svals), 1, file);
            fread(newAsset2->ivals, sizeof(newAsset2->ivals), 1, file);
            newNode->data = newAsset2;
        } else if (strcmp(assetType, "asset3") == 0) {
            Asset3* newAsset3 = (Asset3*)malloc(sizeof(Asset3));
            fread(newAsset3->type, sizeof(newAsset3->type), 1, file);
            fread(newAsset3->string1, sizeof(newAsset3->string1), 1, file);
            fread(newAsset3->string2, sizeof(newAsset3->string2), 1, file);
            newNode->data = newAsset3;
        } else if (strcmp(assetType, "asset4") == 0) {
            Asset4* newAsset4 = (Asset4*)malloc(sizeof(Asset4));
            fread(newAsset4->type, sizeof(newAsset4->type), 1, file);
            fread(&newAsset4->value1, sizeof(newAsset4->value1), 1, file);
            fread(&newAsset4->value2, sizeof(newAsset4->value2), 1, file);
            fread(&newAsset4->value3, sizeof(newAsset4->value3), 1, file);
            newNode->data = newAsset4;
        } else {
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

    fclose(file);
}


int main() {
    struct Node* head = NULL;
    fillLinkedList(&head);
    //printLinkedList(head);
    serializeLinkedList(head);
    deserializeLinkedList(head);
    return 0;
}
