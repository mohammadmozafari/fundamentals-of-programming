#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

typedef struct node {
    char name[50];
    char email[50];
    char ad[200];
    char phone[20];
    struct node *next;
}NODE;

NODE *head = NULL;
int counter = 0;

void openBook()
{
    FILE *read = fopen("Database.txt", "r");
    if (read == NULL) return 0;
    NODE *ite = NULL;
    char name[50], email[50], ad[200], phone[50];
    if (!feof(read))
    {
        head = (NODE*)malloc(sizeof(NODE));
        fscanf(read, "%s%s%s%s", head->name, head->email, head->ad, head->phone);
        counter++;
    }
    ite = head;
    while (!feof(read))
    {
        ite->next = (NODE*)malloc(sizeof(NODE));
        ite = ite->next;
        fscanf(read, "%s%s%s%s", ite->name, ite->email, ite->ad, ite->phone);
        counter++;
    }
    ite->next = NULL;
    fclose(read);
}

void showMenu()
{
    printf("\n---------------------------------------------------\n");
    printf("Don't use space in your input. Use - instead.\n");
    printf("1 - Add new contact\n");
    printf("2 - Show contact list\n");
    printf("3 - Delete a contact\n");
    printf("4 - Edit an existing contact\n");
    printf("5 - Search contact\n");
    printf("6 - Starting with a letter\n");
    printf("7 - How many?\n");
    printf("8 - Exit\n");
    printf("Enter your choice : ");
}

void addContact()
{
    NODE *ite = head;
    if (head != NULL)
    {
        while (ite->next != NULL)
            ite = ite->next;
        ite->next = (NODE*)malloc(sizeof(NODE));
        ite = ite->next;
    }
    else
    {
        head = (NODE*)malloc(sizeof(NODE));
        ite = head;
    }
    fflush(stdin);
    printf("Enter name : ");
    scanf("%s", ite->name);
    fflush(stdin);
    printf("Enter email : ");
    scanf("%s", ite->email);
    fflush(stdin);
    printf("Enter address : ");
    scanf("%s", ite->ad);
    fflush(stdin);
    printf("Enter phone number : ");
    scanf("%s", ite->phone);
    fflush(stdin);
    ite->next = NULL;
    counter++;
}

void printList()
{
    NODE *ite;
    int i = 0;
    ite = head;
    while (ite!=NULL)
    {
        printf("%d\nNAME : %s\nEMAIL : %s\nADDRESS : %s\nPHONE : %s\n****\n", ++i, ite->name, ite->email, ite->ad, ite->phone);
        ite = ite->next;
    }
}

void deleteContact()
{
    if (counter == 0)
    {
        printf("There are no contacts to be deleted.\n");
        return;
    }
    int del, i;
    NODE *ite = head, *temp;
    printList();
    printf("Enter the number of the contact you like to delete : ");
    scanf("%d", &del);
    if (del == 1)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
    else
    {
        for (i = 0 ; i < del-2 ; i++)
            ite = ite->next;
        temp = ite->next->next;
        free(ite->next);
        ite->next = temp;
    }
    counter--;
    if (counter == 0) system("del Database.txt");
}

void editContact()
{
    int edit, i;
    NODE *ite = head;
    printList();
    printf("Enter the number of the contact you like to edit : ");
    scanf("%d", &edit);
    for (i = 0 ; i < edit-1 ; i++)
        ite = ite->next;
    fflush(stdin);
    printf("Enter name : ");
    scanf("%s", ite->name);
    fflush(stdin);
    printf("Enter email : ");
    scanf("%s", ite->email);
    fflush(stdin);
    printf("Enter address : ");
    scanf("%s", ite->ad);
    fflush(stdin);
    printf("Enter phone number : ");
    scanf("%s", ite->phone);
    fflush(stdin);
}

int compareSt(char s1[50], char s2[50])
{
    int i;
    for (i = 0 ; i < strlen(s1) && i < strlen(s2) ; i++)
    {
        if (s1[i] > s2[i]) return 1;
        else if (s1[i] < s2[i]) return -1;
    }
    if (strlen(s1) > strlen(s2)) return 1;
    else if (strlen(s1) < strlen(s2)) return -1;
    return 0;
}

void sort()
{
    int i, j, k;
    NODE *ite = head;
    NODE *temp, *temp2;
    for (i = 0 ; i < counter-1 ; i++)
    {
        for (j = 0 ; j < counter-i-1 ; j++)
        {
            if (j == 0)
            {
                if (compareSt(ite->name, ite->next->name) == 1)
                {
                    temp2 = ite->next;
                    temp = ite->next->next;
                    ite->next->next = ite;
                    ite->next = temp;
                    head = temp2;
                }
            }
            else
            {
                for (k = 0 ; k < j-1 ; k++)
                    ite = ite->next;

                if (compareSt(ite->next->name, ite->next->next->name) == 1)
                {
                    temp2 = ite->next;
                    ite->next = ite->next->next;
                    ite = temp2;
                    temp = ite->next->next;
                    ite->next->next = ite;
                    ite->next = temp;
                }
            }
            ite = head;
        }
    }

}

int equals(char s1[50], char s2[50])
{
    int i;
    if (strlen(s1) != strlen(s2)) return 0;
    for (i = 0 ; i < strlen(s1) ; i++)
        if (s1[i] != s2[i]) return 0;
    return 1;
}

void search()
{
    int choice, i, flag = 0;
    char search[50];
    NODE *ite = head;
    printf("1 - Name\n2 - Phone\n");
    printf("Which one do you like to search : ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 1:
        printf("Enter name : ");
        scanf("%s", search);
        for (i = 0 ; i < counter ; i++)
        {
            if (equals(ite->name, search) == 1)
            {
                printf("%d\nNAME : %s\nEMAIL : %s\nADDRESS : %s\nPHONE : %s\n****\n", i+1, ite->name, ite->email, ite->ad, ite->phone);
                flag = 1;
            }
            ite = ite->next;
        }
        if (flag == 0) printf("No such name exists\n");
        return;
    case 2:
        printf("Enter phone : ");
        scanf("%s", search);
        for (i = 0 ; i < counter ; i++)
        {
            if (equals(ite->phone, search) == 1)
            {
                printf("%d\nNAME : %s\nEMAIL : %s\nADDRESS : %s\nPHONE : %s\n****\n", i+1, ite->name, ite->email, ite->ad, ite->phone);
                flag = 1;
            }
            ite = ite->next;
        }
        if (flag == 0) printf("No such phone exists\n");
        return;
    }
}

void searchLetter()
{
    char start, i;
    NODE *ite = head;
    fflush(stdin);
    printf("Enter a letter : ");
    start = getchar();
    for (i = 0 ; i < counter ; i++)
    {
        if (ite->name[0] == start)
            printf("%d\nNAME : %s\nEMAIL : %s\nADDRESS : %s\nPHONE : %s\n****\n", i+1, ite->name, ite->email, ite->ad, ite->phone);
        ite = ite->next;
    }
}

void saveData()
{
    FILE *write = fopen("Database.txt", "w");
    NODE *ite = head;
    int i;
    for (i = 0 ; i < counter ; i++)
    {
        if (i == 0) fprintf(write, "%s %s %s %s", ite->name, ite->email, ite->ad, ite->phone);
        else fprintf(write, "\n%s %s %s %s", ite->name, ite->email, ite->ad, ite->phone);
        ite = ite->next;
    }
}

int main()
{
    int choice;
    openBook();
    while (1)
    {
        system("CLS");
        showMenu();
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            addContact();
            sort();
            break;
        case 2:
            printList();
            break;
        case 3:
            deleteContact();
            sort();
            break;
        case 4:
            editContact();
            sort();
            break;
        case 5:
            search();
            break;
        case 6:
            searchLetter();
            break;
        case 7:
            printf("There are %d contacts in the book\n", counter);
            break;
        case 8:
            if (counter != 0) saveData();
            return 0;
        }
        printf("Enter any key to continue");
        getch();
    }
    return 0;
}

