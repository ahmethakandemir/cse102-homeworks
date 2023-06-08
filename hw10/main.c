#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct books {
    char isbn[15];
    char title[30];
    char author[20];
    int publicationYear;
    int method;
    struct books* next;
} book;

book* books = NULL;

typedef struct students {
    char name[20];
    char id[20];
    char borrowedBooks[15][25];
} student;

student* students = NULL;

void addBook(char* isbn, char* title, char* author, int publicationYear, int method) {
    // Create a new book
    book* newBook = (book*)malloc(sizeof(book));
    strcpy(newBook->isbn, isbn);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->publicationYear = publicationYear;
    newBook->method = method;
    newBook->next = NULL;

    // If the linked list is empty, assign the new book as the head
    if (books == NULL) {
        books = newBook;
    } else {
        // Find the last book in the linked list
        book* currentBook = books;
        while (currentBook->next != NULL) {
            currentBook = currentBook->next;
        }

        // Assign the new book as the next book of the last book
        currentBook->next = newBook;
    }
}

void txttoll(){
    FILE* file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read the file line by line using fscanf
    char isbn[15];
    char title[30];
    char author[20];
    int publicationYear;

    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", isbn, title, author, &publicationYear) == 4) {
        // Add the book to the linked list
        addBook(isbn, title, author, publicationYear, 0);
    }

    // Close the file
    fclose(file);

}

int main() {
    book* currentBook = books;
    txttoll();

    int selection,method;
    while(1){
        char isbn[15] = {'\0'};
        char title[30]= {'\0'};
        char author[20] = {'\0'};
        int publicationYear = 0;
        printf("enter selection: ");
        scanf("%d",&selection);
        while (getchar() != '\n');
        switch (selection){
        case 1:
            printf("select method (0 or 1): ");
            scanf("%d",&method);
            if(method == 0){
                printf("enter values:");
                scanf("%s,%s,%s,%d\n", isbn, title, author, &publicationYear);
                while (getchar() != '\n');
                addBook(isbn, title, author, publicationYear, 0);
            }
            else if(method == 1){
                scanf("%[^,],%[^,],%[^,],%d\n", isbn, title, author, &publicationYear);
                addBook(isbn, title, author, publicationYear, 1);    
            }
            break;
        case 2:
            printf("");


        case 9:
            printf("exitted!!");
            return 0;
        default:
            break;
        }
    }
    
    
    
    // Free the memory allocated for the books
    
    while (currentBook != NULL) {
        book* nextBook = currentBook->next;
        free(currentBook);
        currentBook = nextBook;
    }

    return 0;
}
