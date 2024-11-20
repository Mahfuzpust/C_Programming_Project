
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 2000

struct Book {
    int id;
    char title[50];
    char author[50];
    int available; // 1: available, 0: issued
};

struct Book library[MAX_BOOKS];
int book_count = 0;

void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    struct Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    getchar(); // clear input buffer
    printf("Enter Book Title: ");
    fgets(newBook.title, 50, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // remove newline
    printf("Enter Author Name: ");
    fgets(newBook.author, 50, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; // remove newline
    newBook.available = 1; // Mark as available

    library[book_count++] = newBook;
    printf("Book added successfully!\n");
}

void displayBooks() {
    if (book_count == 0) {
        printf("No books in the library!\n");
        return;
    }
    printf("\n%-10s %-30s %-30s %-10s\n", "ID", "Title", "Author", "Status");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < book_count; i++) {
        printf("%-10d %-30s %-30s %-10s\n", library[i].id, library[i].title, library[i].author,
               library[i].available ? "Available" : "Issued");
    }
}

void searchBook() {
    char search[50];
    getchar(); // clear input buffer
    printf("Enter title or author to search: ");
    fgets(search, 50, stdin);
    search[strcspn(search, "\n")] = '\0'; // remove newline

    printf("\n%-10s %-30s %-30s %-10s\n", "ID", "Title", "Author", "Status");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < book_count; i++) {
        if (strstr(library[i].title, search) || strstr(library[i].author, search)) {
            printf("%-10d %-30s %-30s %-10s\n", library[i].id, library[i].title, library[i].author,
                   library[i].available ? "Available" : "Issued");
        }
    }
}

void issueBook() {
    int id;
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].available) {
                library[i].available = 0;
                printf("Book issued successfully!\n");
                return;
            } else {
                printf("Book is already issued.\n");
                return;
            }
        }
    }
    printf("Book not found!\n");
}

void returnBook() {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (!library[i].available) {
                library[i].available = 1;
                printf("Book returned successfully!\n");
                return;
            } else {
                printf("Book is already available.\n");
                return;
            }
        }
    }
    printf("Book not found!\n");
}

void menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Search Book\n");
    printf("4. Issue Book\n");
    printf("5. Return Book\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    do {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

