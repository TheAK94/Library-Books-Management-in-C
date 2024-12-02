#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char title[50];
    char author[50];
    int is_issued;
} Book;

// Function Declarations
void displayMenu();
void addBook();
void viewBooks();
void searchBook(int id_query, char *query);
void issueBook(int id_query, char *query);
void returnBook(int id_query, char *query);
void deleteBook(int id_query, char *query);

int main()
{
    int choice, issue_choice, issue_id, search_choice, search_id, return_choice, delete_choice, delete_id;
    char query[50];

    do
    {
        displayMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                printf("SEARCH BOOK: \n1. Search by Name \n2. Search by ID\nEnter choice: ");
                scanf("%d", &search_choice);
                if (search_choice == 1)
                {
                    printf("Enter name: ");
                    scanf("%s", query);
                    searchBook(-1, query);
                } else if (search_choice == 2)
                {
                    printf("Enter ID: ");
                    scanf("%d", &search_id);
                    searchBook(search_id, NULL);
                } else printf("INVALID INPUT!\n");
                break;
            case 4:
                printf("ISSUE BOOK: \n1. Search by Name \n2. Search by ID\nEnter choice: ");
                scanf("%d", &issue_choice);
                if (issue_choice == 1)
                {
                    printf("Enter name: ");
                    scanf("%s", query);
                    issueBook(-1, query);
                } else if (issue_choice == 2)
                {
                    printf("Enter ID: ");
                    scanf("%d", &issue_id);
                    issueBook(issue_id, NULL);
                } else printf("INVALID INPUT!\n");
                break;
            case 5:
                printf("RETURN BOOK: \n1. Search by Name \n2. Search by ID\nEnter choice: ");
                scanf("%d", &return_choice);
                if (return_choice == 1)
                {
                    printf("Enter name: ");
                    scanf("%s", query);
                    returnBook(-1, query);
                } else if (return_choice == 2)
                {
                    printf("Enter ID: ");
                    scanf("%d", &issue_id);
                    returnBook(issue_id, NULL);
                } else printf("INVALID INPUT!\n");
                break;
            case 6:
                printf("DELETE BOOK: \n1. Search by Name \n2. Search by ID\nEnter choice: ");
                scanf("%d", &delete_choice);
                if (delete_choice == 1)
                {
                    printf("Enter name: ");
                    scanf("%s", query);
                    deleteBook(-1, query);
                } else if (delete_choice == 2)
                {
                    printf("Enter ID: ");
                    scanf("%d", &delete_id);
                    deleteBook(delete_id, NULL);
                } else printf("INVALID INPUT!\n");
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default :
                printf("INVALID INPUT.\n");
                break;

        }

    } while (choice != 7);
    return 0;
}

// FUNCTIONS
void displayMenu()
{
    printf("------MAIN MENU------\n");
    printf("1. Add a new book\n");
    printf("2. View all books\n");
    printf("3. Search book\n");
    printf("4. Issue a book\n");
    printf("5. Return a book\n");
    printf("6. Delete a book\n");
    printf("7. Exit\n");
}

void addBook()
{
    FILE *file = fopen("library.dat", "ab");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Book newBook;
    printf("Enter ID: ");
    scanf("%d", &newBook.id);
    printf("Enter Title: ");
    scanf("%49s", &newBook.title);
    printf("Enter Author: ");
    scanf("%49s", &newBook.author);
    newBook.is_issued = 0;

    fwrite(&newBook, sizeof(Book), 1, file);
    printf("Book added successfully!\n");
    fclose(file);
}

void viewBooks()
{
    FILE *file = fopen("library.dat", "rb");
    if (file == NULL)
    {
        printf("No records found!\n");
        return;
    }

    Book temp;
    printf("------BOOKS------\n");

    while (fread(&temp, sizeof(Book), 1, file) == 1)
    {
        printf("Book ID: %d\n", temp.id);
        printf("Title: %s\n", temp.title);
        printf("Author: %s\n", temp.author);
        if (temp.is_issued == 1)
        {
            printf("Status: Issued\n");
        } else printf("Status: Not issued\n");
        printf("---------------------\n");
    }
    fclose(file);
}

void searchBook(int id_query, char *query)
{
    FILE *file = fopen("library.dat", "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Book temp;
    int found = 0;

    while (fread(&temp, sizeof(Book), 1, file) == 1)
    {
        if ((id_query != -1 && temp.id == id_query) || (query != NULL && strcmp(temp.title, query)== 0))
        {
            found = 1;
            printf("------BOOK FOUND------\n");
            printf("Book ID: %d\n", temp.id);
            printf("Title: %s\n", temp.title);
            printf("Author: %s\n", temp.author);
            if (temp.is_issued == 1)
            {
                printf("Status: Issued\n");
            } else printf("Status: Not issued\n");
            printf("---------------------\n");
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }
    fclose(file);
}

void issueBook(int id_query, char *query)
{
    FILE *file = fopen("library.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Book temp;
    int found = 0;

    while (fread(&temp, sizeof(Book), 1, file) == 1)
    {
        if ((id_query != -1 && temp.id == id_query) || (query != NULL && strcmp(temp.title, query)== 0))
        {
            found = 1;

            if (temp.is_issued == 0)
            {
                temp.is_issued = 1;

                fseek(file, -sizeof(Book), SEEK_CUR);
                fwrite(&temp, sizeof(Book), 1, file);
                printf("Book issued successfully!\n");
            } else printf("Book already issued.\n");
            break;
        }
    }
    if (!found) 
    {
        printf("Book not found.\n");
    }
    fclose(file);
}

void returnBook(int id_query, char *query)
{
    FILE *file = fopen("library.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Book temp;
    int found = 0;

    while (fread(&temp, sizeof(Book), 1, file) == 1)
    {
        if ((id_query != -1 && temp.id == id_query) || (query != NULL && strcmp(temp.title, query)== 0))
        {
            found = 1;

            if (temp.is_issued == 1)
            {
                temp.is_issued = 0;

                fseek(file, -sizeof(Book), SEEK_CUR);
                fwrite(&temp, sizeof(Book), 1, file);
                printf("Book returned successfully!\n");
            } else printf("Book not issued.\n");
            break;
        }
    }
    if (!found) 
    {
        printf("Book not found.\n");
    }
    fclose(file);
}

void deleteBook(int id_query, char *query)
{
    FILE *file = fopen("library.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL) 
    {
        printf("Error opening files.\n");
        return;
    }

    Book temp_book;
    int found = 0;

    while (fread(&temp_book, sizeof(Book), 1, file) == 1) 
    {
        if (!((id_query != -1 && temp_book.id == id_query) || 
              (query != NULL && strcmp(temp_book.title, query) == 0))) 
        {
            fwrite(&temp_book, sizeof(Book), 1, temp);
        } 
        else 
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found) 
    {
        printf("Book deleted successfully!\n");
    } 
    else 
    {
        printf("Book not found.\n");
    }
}
