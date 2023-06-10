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
void printBooks() {
    book* currentBook = books;
    while (currentBook != NULL) {
        printf("ISBN: %s\n", currentBook->isbn);
        printf("Title: %s\n", currentBook->title);
        printf("Author: %s\n", currentBook->author);
        printf("Publication Year: %d\n", currentBook->publicationYear);
        printf("-----------------------------\n");
        currentBook = currentBook->next;
    }
}
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
        // Add the new book at the beginning or end based on the method chosen
        if (method == 0) {
            // FIFO - Add the new book at the end
            book* currentBook = books;
            while (currentBook->next != NULL) {
                currentBook = currentBook->next;
            }
            currentBook->next = newBook;
        } else if (method == 1) {
            // LIFO - Add the new book at the beginning
            newBook->next = books;
            books = newBook;
        }
    }
}


void txttoll() {
    // Free memory for existing books
    book* currentBook = books;
    while (currentBook != NULL) {
        book* nextBook = currentBook->next;
        free(currentBook);
        currentBook = nextBook;
    }

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

void deleteBook(char* isbn) {
    FILE* file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    book* currentBook = books;
    while (currentBook != NULL) {
        if (strcmp(currentBook->isbn, isbn) != 0) {
            fprintf(file, "%s,%s,%s,%d\n", currentBook->isbn, currentBook->title, currentBook->author, currentBook->publicationYear);
        }
        currentBook = currentBook->next;
    }

    fclose(file);

    // Update the linked list by reading the modified file
    txttoll();
}

void addtotxt(char* isbn, char* title, char* author, int publicationYear, int method) {
    FILE* file = fopen("books.txt", "a+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    if (method == 0) {
        // Append the book information at the end of the file
        fprintf(file, "%s,%s,%s,%d\n", isbn, title, author, publicationYear);
    } else if (method == 1) {
        // Create a temporary file and write the new book information at the beginning
        FILE* tempFile = fopen("temp.txt", "w");
        fprintf(tempFile, "%s,%s,%s,%d\n", isbn, title, author, publicationYear);

        // Append the existing book information from the original file
        char bookInfo[100];
        while (fgets(bookInfo, sizeof(bookInfo), file) != NULL) {
            fprintf(tempFile, "%s", bookInfo);
        }

        // Close both files
        fclose(file);
        fclose(tempFile);

        // Remove the original file and rename the temporary file
        remove("books.txt");
        rename("temp.txt", "books.txt");

        // Reopen the file for appending future books
        file = fopen("books.txt", "a+");
        if (file == NULL) {
            printf("Failed to open the file after rearranging.\n");
            return;
        }
    }

    fclose(file);
}


void lltotxt() {
    book* currentBook = books;
    FILE* file = fopen("books.txt", "w");
    while (currentBook != NULL) {
        fprintf(file, "%s,%s,%s,%d\n", currentBook->isbn, currentBook->title, currentBook->author, currentBook->publicationYear);
        currentBook = currentBook->next;
    }
    fclose(file);
}

void updateBook(char* isbn, char* feature, char* value) {
    book* currentbook = books;

    while (currentbook != NULL && strcmp(isbn, currentbook->isbn) != 0) {
        currentbook = currentbook->next;
    }

    if (currentbook == NULL) {
        printf("Book not found.\n");
        return;
    }

    if (strcmp(feature, "1") == 0) {
        strcpy(currentbook->title, value);
    } else if (strcmp(feature, "2") == 0) {
        strcpy(currentbook->author, value);
    } else if (strcmp(feature, "3") == 0) {
        currentbook->publicationYear = atoi(value);
    }

    lltotxt();
}

int main() {
    book* currentBook = books;
    txttoll();
    //printBooks();
    int selection,method;
    char isbn[15];
    char title[30];
    char author[20];
    int publicationYear;
    char feature[2];
    char newvalue[100];
    while(1){
        printf("1. Show a student's borrowed books list\n");
        printf("2. Add book to library\n");
        printf("3. Delete a book\n");
        printf("4. Update a book's feature\n");
        printf("5. Filter and Sort books");
        printf("9. Terminate the program\n");
        printf("Enter selection: ");
        scanf("%d",&selection);
        while (getchar() != '\n');
        switch (selection){
        case 1:
            printf("\nBu part henuz yapilmadi!!\n\n");
            break;
        case 2:
            printf("select method (0 or 1): ");
            scanf("%d",&method);
            if(method == 0){
                printf("enter values seperated with comma(,):(ISBN,title,author,publication year):  ");
                scanf(" %[^,\n],%[^,\n],%[^,\n],%d", isbn, title, author, &publicationYear);
                while (getchar() != '\n');
                addBook(isbn, title, author, publicationYear, 0);
                addtotxt(isbn, title, author, publicationYear,0);
                //printBooks();
            }
            else if(method == 1){
                scanf(" %[^,\n],%[^,\n],%[^,\n],%d", isbn, title, author, &publicationYear);
                addBook(isbn, title, author, publicationYear, 1);    
                addtotxt(isbn, title, author, publicationYear,1);
                //printBooks();
            }
            break;
        case 3:
            printf("\nEnter the ISBN number of the book you want to delete: ");
            scanf("%s",isbn);
            deleteBook(isbn);
            break;
        case 4:
            printf("Enter the ISBN of the book you want to change a value of it: ");
            scanf("%s", isbn);
            while (getchar() != '\n');  // Clear the input buffer

            printf("\n1. Title\n2. Author\n3. Publication Year\nEnter the feature: ");
            scanf("%s", feature);
            printf("Enter the new value for the selected feature: ");
            scanf(" %[^\n]", newvalue);
            updateBook(isbn, feature, newvalue);
            //printBooks();
            break;

        case 9:
            printf("\nExitted!!\n");
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
