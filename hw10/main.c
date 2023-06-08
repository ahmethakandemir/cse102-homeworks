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

int main() {
    // Open the file for reading
    FILE* file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
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

    // Print the title of each book in the list
    book* currentBook = books;
    while (currentBook != NULL) {
        printf("Title: %s\n", currentBook->title);
        currentBook = currentBook->next;
    }

    // Free the memory allocated for the books
    currentBook = books;
    while (currentBook != NULL) {
        book* nextBook = currentBook->next;
        free(currentBook);
        currentBook = nextBook;
    }

    return 0;
}
