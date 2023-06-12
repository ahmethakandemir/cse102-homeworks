#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct books {
    char isbn[15];
    char title[30];
    char author[20];
    int publicationYear;
    int reservedStatus;
    int method;
    struct books* next;
} book;

book* books = NULL;

typedef struct students {
    char name[20];
    char id[20];
    char borrowedBooks[15][25];
    int borrowedCounter;
    struct students* next;

} student;

student* students = NULL;
void prntBooks() {
    book* currentBook = books;
    while (currentBook != NULL) {
        printf("ISBN: %s\n", currentBook->isbn);
        printf("Title: %s\n", currentBook->title);
        printf("Author: %s\n", currentBook->author);
        printf("Publication Year: %d\n", currentBook->publicationYear);
        printf("Reserved Status: %d\n",currentBook->reservedStatus);
        printf("-----------------------------\n");
        currentBook = currentBook->next;
    }
}
void addBook(char* isbn, char* title, char* author, int publicationYear, int method,int reservedStatus) {
    int flag = 0;
    book* tempbook = books;
    while(tempbook != NULL){
        if(strcmp(tempbook->isbn,isbn) == 0){
            flag = 1;
        }
        tempbook = tempbook->next;
    }
    // Create a new book
    if(flag == 0){
        book* newBook = (book*)malloc(sizeof(book));
        strcpy(newBook->isbn, isbn);
        strcpy(newBook->title, title);
        strcpy(newBook->author, author);
        newBook->publicationYear = publicationYear;
        newBook->method = method;
        newBook->reservedStatus = reservedStatus;
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
    else if(flag == 1){
        printf("\nThere is already a book that recorded with the same ISBN!!\n");
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
    int reservedStatus;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d\n", isbn, title, author, &publicationYear,&reservedStatus) == 5) {
        // Add the book to the linked list
        addBook(isbn, title, author, publicationYear, 0,reservedStatus);
    }

    // Close the file
    fclose(file);
}

void deleteBook(char* isbn) {
    book* current = books;
    book* prev = NULL;

    // Traverse the linked list to find the book with the given ISBN
    while (current != NULL) {
        if (strcmp(current->isbn, isbn) == 0) {
            // Book found, remove it from the linked list
            if (prev == NULL) {
                // Book is the first node
                books = current->next;
            } else {
                // Book is somewhere in the middle or at the end
                prev->next = current->next;
            }

            free(current);
            printf("Book with ISBN %s has been deleted.\n", isbn);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Book with ISBN %s not found.\n", isbn);
}
void addtotxt(char* isbn, char* title, char* author, int publicationYear, int method) {
    FILE* file = fopen("books.txt", "a+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    if (method == 0) {
        // Append the book information at the end of the file
        fprintf(file, "%s,%s,%s,%d,%d\n", isbn, title, author, publicationYear,0);
    } else if (method == 1) {
        // Create a temporary file and write the new book information at the beginning
        FILE* tempFile = fopen("temp.txt", "w");
        fprintf(tempFile, "%s,%s,%s,%d,%d\n", isbn, title, author, publicationYear,0);

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
        fprintf(file, "%s,%s,%s,%d,%d\n", currentBook->isbn, currentBook->title, currentBook->author, currentBook->publicationYear,currentBook->reservedStatus);
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



void txttostudents() {
    FILE* studentstxt = fopen("students.txt", "r");
    if (studentstxt == NULL) {
        printf("Unable to open students.txt\n");
        return;
    }

    student* currentStudent = NULL;
    student* prevStudent = NULL;
    int flag = 0;
    while (!feof(studentstxt)) {
        currentStudent = (student*)malloc(sizeof(student));
        if (currentStudent == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        currentStudent->next = NULL;
        if(flag > 0){
            fgetc(studentstxt);
        }
        else{
            flag++;
        }
        if (fscanf(studentstxt, "%[^,],%[^,],", currentStudent->name, currentStudent->id) != 2) {
            free(currentStudent);
            continue;
        }

        for (int i = 0; i < 10; i++) {
            if (fscanf(studentstxt, "%[^,\n],", currentStudent->borrowedBooks[i]) == 1) {
                currentStudent->borrowedCounter = i + 1;
            } else {
                break;
            }
        }

        if (students == NULL) {
            students = currentStudent;
        } else {
            prevStudent->next = currentStudent;
        }
        prevStudent = currentStudent;
    }

    fclose(studentstxt);
}

void prtnstudents() {
    student* currentStudent = students;
    while (currentStudent != NULL) {
        printf("Name: %s\n", currentStudent->name);
        printf("ID: %s\n", currentStudent->id);
        for (int i = 0; i < currentStudent->borrowedCounter; i++) {
            printf("Borrowed book %d: %s\n", i + 1, currentStudent->borrowedBooks[i]);
        }
        printf("-----------------------------\n");
        currentStudent = currentStudent->next;
    }
}

void borrowBook(char* isbn){
    char studentid[20];
    char tempisbn[20];
    printf("\nEnter the students ID to give it the book to student: ");
    scanf("%s",studentid);
    book * currentBook = books;
    student * currentStudent = students;
    while (currentBook != NULL){
        if(strcmp(currentBook->isbn,isbn) == 0){
            if(currentBook->reservedStatus == 1){
                printf("\nThis book is already borrowed!!!!!!!!!\n");
                return;
            }
            currentBook->reservedStatus = 1;
            strcpy(tempisbn,currentBook->isbn);
        }
        currentBook = currentBook->next;
    }
    while(currentStudent != NULL){
        if(strcmp(currentStudent->id,studentid) == 0){
            strcpy(currentStudent->borrowedBooks[students->borrowedCounter],tempisbn);
            currentStudent->borrowedCounter++;
        }
        currentStudent = currentStudent->next;
    }
}



void freeStudents() {
    student* currentStudent = students;
    while (currentStudent != NULL) {
        student* temp = currentStudent;
        currentStudent = currentStudent->next;
        free(temp);
    }
    students = NULL;
}

void studentsBorrowedBooks(char * id){
    printf("\n");
    student * currentStudent = students;
    while(currentStudent != NULL){
        if(strcmp(currentStudent->id,id) == 0){
            printf("Student's number and name is: %s,%s\nBorrowed books are: ",currentStudent->id,currentStudent->name);
            for(int i = 0;i < currentStudent->borrowedCounter;i++){
                printf("%s,",currentStudent->borrowedBooks[i]);
            }
        }
        currentStudent = currentStudent->next;
    }
    printf("\n\n");
}

void returnBook(char* isbn){

    student * currentStudent = students;
    book * currentBook = books;

    while(1){
        if(currentBook == NULL){
            break;
        }
        if(strcmp(currentBook->isbn,isbn) == 0){
            currentBook->reservedStatus = 0;
        }
        currentBook = currentBook->next;
    }
    currentBook = books;
    int j;
    while(currentStudent != NULL){
        for(int i = 0;i < currentStudent->borrowedCounter; i++){
            if(strcmp(currentStudent->borrowedBooks[i],isbn) == 0){
                for(j = i;j < currentStudent->borrowedCounter;j++){
                    strcpy(currentStudent->borrowedBooks[j],currentStudent->borrowedBooks[j+1]);
                }
            }
        }
        currentStudent = currentStudent->next;
    }
}


void studentstotxt(){
    student* currentStudent = students;
    FILE* file = fopen("students.txt", "w");
    while (currentStudent != NULL) {
        fprintf(file, "%s,%s,", currentStudent->name, currentStudent->id);
        for(int i = 0; i < currentStudent->borrowedCounter;i++){
            fprintf(file,"%s",currentStudent->borrowedBooks[i]);
            if(i != currentStudent->borrowedCounter - 1){
                fprintf(file,",");
            }
        }
        if(currentStudent->next != NULL){
            fprintf(file,"\n");
        }
        currentStudent = currentStudent->next;
    }
    fclose(file);
}

void reverseBookList() {
    book* tempbooks = NULL;
    book* currentBook = books;
    book* nextBook;

    while (currentBook != NULL) {
        nextBook = currentBook->next;
        currentBook->next = tempbooks;
        tempbooks = currentBook;
        currentBook = nextBook;
    }

    books = tempbooks; // Update the head of the list to the reversed list

    // Set the next pointer of the last book to NULL
    if (tempbooks != NULL) {
        book* lastBook = tempbooks;
        while (lastBook->next != NULL) {
            lastBook = lastBook->next;
        }
        lastBook->next = NULL;
    }
    books = tempbooks;
    lltotxt();
}
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice, book* library) {
    book* filteredBooks = NULL;
    book* sortedBooks = NULL;
    book* current = books;

    // Filter books based on the given criteria
    while (current != NULL) {
        if (filterChoice == 0) {
            if (strcmp(current->author, filter) == 0) {
                // Book matches the author filter
                // Add it to the filtered books list
                book* newBook = (book*)malloc(sizeof(book));
                strcpy(newBook->isbn, current->isbn);
                strcpy(newBook->title, current->title);
                strcpy(newBook->author, current->author);
                newBook->publicationYear = current->publicationYear;
                newBook->reservedStatus = current->reservedStatus;
                newBook->method = current->method;
                newBook->next = filteredBooks;
                filteredBooks = newBook;
            }
        } else if (filterChoice == 1) {
            if (current->publicationYear == atoi(filter)) {
                // Book matches the publication year filter
                // Add it to the filtered books list
                book* newBook = (book*)malloc(sizeof(book));
                strcpy(newBook->isbn, current->isbn);
                strcpy(newBook->title, current->title);
                strcpy(newBook->author, current->author);
                newBook->publicationYear = current->publicationYear;
                newBook->reservedStatus = current->reservedStatus;
                newBook->method = current->method;
                newBook->next = filteredBooks;
                filteredBooks = newBook;
            }
        }

        current = current->next;
    }

    // Sort the filtered books based on the given sort choice
    while (filteredBooks != NULL) {
        book* nextBook = filteredBooks->next;
        if (sortedBooks == NULL || sortChoice == 0 || sortChoice == 1) {
            // Sort by title or author (alphabetically)
            book* prev = NULL;
            book* curr = sortedBooks;
            while (curr != NULL && strcmp(filteredBooks->title, curr->title) > 0) {
                prev = curr;
                curr = curr->next;
            }
            if (prev == NULL) {
                filteredBooks->next = sortedBooks;
                sortedBooks = filteredBooks;
            } else {
                prev->next = filteredBooks;
                filteredBooks->next = curr;
            }
        } else if (sortChoice == 2) {
            // Sort by publication year (ascending)
            book* prev = NULL;
            book* curr = sortedBooks;
            while (curr != NULL && filteredBooks->publicationYear > curr->publicationYear) {
                prev = curr;
                curr = curr->next;
            }
            if (prev == NULL) {
                filteredBooks->next = sortedBooks;
                sortedBooks = filteredBooks;
            } else {
                prev->next = filteredBooks;
                filteredBooks->next = curr;
            }
        }
        filteredBooks = nextBook;
    }

    // Print the filtered and sorted books
    printf("Filtered and sorted books:\n");
    current = sortedBooks;
    while (current != NULL) {
        printf("ISBN: %s\n", current->isbn);
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("Publication Year: %d\n", current->publicationYear);
        printf("Reserved Status: %d\n", current->reservedStatus);
        printf("Method: %d\n", current->method);
        printf("\n");
        current = current->next;
    }
}

int main() {
    book* currentBook = books;
    txttoll();
    //prntBooks();
    int selection,method;
    char isbn[15];
    char title[30];
    char author[20];
    int publicationYear;
    char feature[2];
    char newvalue[100];
    char id[20];
    int filterChoice;
    char filter[50];
    int sortChoice;
    while(1){
        printf("1. Show a student's borrowed books list\n");
        printf("2. Add book to library\n");
        printf("3. Delete a book\n");
        printf("4. Update a book's feature\n");
        printf("5. Filter and Sort books\n");
        printf("6. Reverse book list\n");
        printf("7. Borrow books\n");
        printf("8. Return Books\n");
        printf("9. Print all the books in the library\n");
        printf("10. Print all the students borrowed books and informations\n");
        printf("0. Terminate the program\n");
        printf("Enter selection: ");
        scanf("%d",&selection);
        while (getchar() != '\n');
        switch (selection){
        case 1:
            txttostudents();
            printf("Please enter the id of the student that you want to see which books are borrowed: ");
            scanf("%s",id);
            studentsBorrowedBooks(id);
            studentstotxt();
            freeStudents();
            break;
        case 2:
            printf("select method (0 or 1): ");
            scanf("%d",&method);
            if(method == 0){
                printf("enter values seperated with comma(,):(ISBN,title,author,publication year):  ");
                scanf(" %[^,\n],%[^,\n],%[^,\n],%d", isbn, title, author, &publicationYear);
                while (getchar() != '\n');
                addBook(isbn, title, author, publicationYear, 0,0);
                addtotxt(isbn, title, author, publicationYear,0);
                //prntBooks();
            }
            else if(method == 1){
                printf("enter values seperated with comma(,):(ISBN,title,author,publication year):  ");
                scanf(" %[^,\n],%[^,\n],%[^,\n],%d", isbn, title, author, &publicationYear);
                while (getchar() != '\n');
                addBook(isbn, title, author, publicationYear, 1,0);
                addtotxt(isbn, title, author, publicationYear,1);
                //prntBooks();
            }
            break;
        case 3:
            printf("\nEnter the ISBN number of the book you want to delete: ");
            scanf("%s",isbn);
            deleteBook(isbn);
            lltotxt();
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
            //prntBooks();
            break;
        case 5:


            printf("Filter and Sort Books\n");
            printf("Enter filter choice (0 for author, 1 for publication year): ");
            scanf("%d", &filterChoice);

            printf("Enter filter criteria: ");
            scanf(" %[^\n]s", filter);

            printf("Enter sort choice (0 for title, 1 for author, 2 for publication year): ");
            scanf("%d", &sortChoice);

            // Call the filterAndSortBooks function with the scanned parameters
            filterAndSortBooks(filterChoice, filter, sortChoice,books);
            lltotxt();
            break;
        case 6:
            reverseBookList();
            break;
        case 7:
            txttostudents();
            printf("\nEnter the ISBN number of the book you want to borrow: ");
            scanf("%s",isbn);
            borrowBook(isbn);
            studentstotxt();
            lltotxt();
            freeStudents();
            break;
        case 8:
            txttostudents();
            printf("\nEnter the ISBN number of the book you want to return: ");
            scanf("%s",isbn);
            returnBook(isbn);
            lltotxt();
            studentstotxt();
            freeStudents();
            break;
        case 9:
            prntBooks();
            break;
        case 10:
            txttostudents();
            prtnstudents();
            freeStudents();
            break;
        case 0:
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
