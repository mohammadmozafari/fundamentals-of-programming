#include <stdio.h>

#define START 33
#define END 126

char key[] = "MFI";

void showMenu();
void createAccount();
void logIn();
void encode(char*, char*);
int areEqual(char*, char*);
int isUsed(char*);
int checkPassword(char*);

int main()
{
    int choice;
    showMenu();
    scanf("%d", &choice);
    switch(choice)
    {
    case 1:
        createAccount();
        break;
    case 2:
        logIn();
        break;
    }
    return 0;
}

void showMenu()
{
    printf("1. Create new account\n");
    printf("2. Log in\n");
}

void createAccount()
{
    char username[100], password[100];
    FILE *data = fopen("Database.txt", "a+");
    do {
        printf("Enter a username : ");
        scanf("%s", username);
    }while (isUsed(username));

    do
    {
        printf("Enter a password : ");
        scanf("%s", password);
    }while (checkPassword(password));
    encode(password, key);
    fprintf(data, "%s\n", username);
    fprintf(data, "%s\n", password);
    fclose(data);
}

void encode(char pass[], char key[])
{
    int i, j = 0, ch1, ch2;
    char newKey[strlen(pass)];
    for (i = 0 ; i < strlen(pass) ; i++)
    {
        if (j == strlen(key)) j = 0;
        newKey[i] = key[j++];
    }
    newKey[i] = NULL;
    for (i = 0 ; i < strlen(pass) ; i++)
    {
        ch1 = (int)pass[i] - START;
        ch2 = (int)newKey[i] - START;
        ch1 = (ch1 + ch2) % (END-START+1);
        ch1+=START;
        pass[i] = (char)ch1;
    }
}

void logIn()
{
    char username[100], password[100], dbUser[100], dbPass[100], temp[100];
    FILE *data = fopen("Database.txt", "r");
    if (data == NULL)
    {
        printf("No database exists.");
        exit(0);
    }
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);
    encode(password, key);
    while (!feof(data))
    {
        fscanf(data, "%s", dbUser);
        if (areEqual(username, dbUser))
        {
            fscanf(data, "%s", dbPass);
            if (areEqual(password, dbPass))
            {
                printf("You are successfully logged in.");
                return;
            }
        }
        else
        {
            fscanf(data, "%s", temp);
        }
    }
    printf("Sorry either username or password is incorrect.");
}

int areEqual(char s1[], char s2[])
{
    int i;
    if (strlen(s1) != strlen(s2)) return 0;
    for (i = 0 ; i < strlen(s1) ; i++)
        if (s1[i] != s2[i]) return 0;
    return 1;
}

int isUsed(char name[])
{
    char user[100];
    FILE *data = fopen("Database.txt", "r");
    while (!feof(data))
    {
        fscanf(data, "%s", user);
        if (areEqual(user, name)) return 1;
    }
    return 0;
}

int checkPassword(char pass[])
{
    int check1 = 0, check2 = 0, check3 = 0, i;
    if (strlen(pass) < 8) return 1;
    for (i = 0 ; i < strlen(pass) ; i++)
    {
        if (pass[i]>=48 && pass[i] <= 57) check1++;
        else if ((pass[i]>=65 && pass[i] <= 90)||(pass[i]>=97 && pass[i] <= 122)) check2++;
        else check3++;
    }
    if (check1 != 0 && check2!=0 && check3!=0) return 0;
    return 1;
}