#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define GAP 30
#define TOP_PADDING 10
#define TOWER_HEIGHT 20
#define MOVE_SPEED 30
#define DRAW_SPEED 15

int moves = 0;
int aDisk, bDisk = 0, cDisk = 0, diskNumber;

void transfer(int, int, int, int);
void showMessage(char[], int);
void drawTowers();
void gotoxy(int, int);
void drawDisk(int, int);
void moveVer(int, int, int);
void moveHor(int, int, int);
void color (int x);

int main()
{
    int messageLength, i;
    char firstMessage1[100] = "WELCOME TO TOWERS OF HANOI GAME.";
    char firstMessage2[100] = "HOW MANY DISKS DO YOU LIKE TO START WITH : ";
    char beginMessage[100] = "ENTER ANY KEY TO BEGIN";
    char finalMessage[100] = "DO YOU LIKE TO TRY AGAIN (ENTER CAPITAL 'Y' OR 'N') ? ";
    char errorMessage[100] = "ENTER ONLY CAPITAL Y OR N : ";
    char retry;

    do
    {
        system("color A");
        showMessage(firstMessage1, strlen(firstMessage1));
        printf("\n");
        showMessage(firstMessage2, strlen(firstMessage2));
        scanf("%d", &diskNumber);
        system("CLS");
        //system("color 1C");
        drawTowers();
        for (i = diskNumber ; i >= 1 ; i--)
            drawDisk(1, i);
        aDisk = diskNumber;
        showMessage(beginMessage, strlen(beginMessage));
        getch();
        transfer(diskNumber, 1, 2, 3);
        showMessage(finalMessage, strlen(finalMessage));
        retry = getch();
        printf("\n");
        while(retry != 'N' && retry != 'Y')
        {
            showMessage(errorMessage, strlen(errorMessage));
            retry = getch();
            printf("\n");
        }
        aDisk = bDisk = cDisk = diskNumber = moves = 0;
        system("CLS");
    }while(retry == 'Y');

    return 0;
}

void transfer(int diskNum, int a, int b, int c)
{
    int size;
    moves++;
    if (diskNum > 1)
    {
        transfer(diskNum-1, a, c, b);

        moveVer(a, 1, diskNum);
        if (a == 1) aDisk--;
        else if (a == 2) bDisk--;
        else if (a == 3) cDisk--;

        moveHor(a, c, diskNum);
        moveVer(c, -1, diskNum);
        if (c == 1) aDisk++;
        else if (c == 2) bDisk++;
        else if (c == 3) cDisk++;

        transfer(diskNum-1, b, a, c);
    }
    else
    {
        moveVer(a, 1, 1);
        moveHor(a, c, 1);
        moveVer(c, -1, 1);
        if (a == 1) aDisk--;
        else if (a == 2) bDisk--;
        else if (a == 3) cDisk--;
        if (c == 1) aDisk++;
        else if (c == 2) bDisk++;
        else if (c == 3) cDisk++;
    }
}

void showMessage(char message[], int strLength)
{
    int i;
    color(7);
    for (i = 0 ; i < strLength ; i++)
    {
        printf("%c", message[i]);
        Sleep(DRAW_SPEED);
    }
    printf("\r");
    color(10);
    for (i = 0 ; i < strLength ; i++)
    {
        printf("%c", message[i]);
        Sleep(DRAW_SPEED);
    }
}

void drawTowers()
{
    int i, j;

    for (i = 15 ; i <= 105 ; i++)
    {
        gotoxy(i, TOWER_HEIGHT + TOP_PADDING + 2);
        printf("%c", 176);
        Sleep(DRAW_SPEED);
    }

    for (i = 0 ; i < 3 ; i++)
    {
        for (j = 0 ; j <= TOWER_HEIGHT; j++)
        {
            gotoxy(GAP*(i+1), j+TOP_PADDING);
            printf("%c", 176);
            Sleep(DRAW_SPEED);
        }
    }
    gotoxy(0,TOP_PADDING+TOWER_HEIGHT+4);

}

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void drawDisk(int tower, int size)
{
    int number = diskNumber - size;
    gotoxy(GAP*(tower)-size-2, TOP_PADDING+(TOWER_HEIGHT)-(number)*2);
    int i;
    for (i = 0 ; i < 2*(size+2)+1;i++)
    {
        printf("%c", 176);
        Sleep(DRAW_SPEED);
    }
    gotoxy(0,TOP_PADDING+(TOWER_HEIGHT)+4);
}

void moveVer(int tower, int UoD, int size)
{
    int towerDisk, i, j;

    if (tower == 1) towerDisk = aDisk;
    if (tower == 2) towerDisk = bDisk;
    if (tower == 3) towerDisk = cDisk;

    if (UoD == 1)
    {
        for (i = 0 ; i <= (TOWER_HEIGHT)-towerDisk*2 + 5 ; i++)
        {
            gotoxy(GAP*tower - size - 2 , TOP_PADDING + (TOWER_HEIGHT)-(towerDisk-1)*2 - i);
            for (j = 0 ; j < 2*(size+2) + 1 ; j++)
            {
                if (j == size+2 && i <= (TOWER_HEIGHT)-towerDisk*2 + 2) printf("%c", 176);
                printf("%c", 0);
            }
            gotoxy(GAP*tower - size - 2 , TOP_PADDING + (TOWER_HEIGHT)-(towerDisk-1)*2 - i - 1);
            for (j = 0 ; j < 2*(size+2) + 1 ; j++)
                printf("%c", 176);
            Sleep(MOVE_SPEED);
        }
    }
    if (UoD == -1)
    {
        for (i = 0 ; i <= (TOWER_HEIGHT)-towerDisk*2 + 4 ; i++)
        {
            gotoxy(GAP*tower - size - 2 , TOP_PADDING - 5 + i);
            for (j = 0 ; j < 2*(size+2) + 1 ; j++)
            {
                if (j == size+2 && i >= 5) printf("%c", 176);
                printf("%c", 0);
            }
            gotoxy(GAP*tower - size - 2 , TOP_PADDING - 5 + i + 1);
            for (j = 0 ; j < 2*(size+2) + 1 ; j++)
                printf("%c", 176);
            Sleep(MOVE_SPEED);
        }
    }
    gotoxy(0, TOP_PADDING + (TOWER_HEIGHT) + 4);
}

void moveHor(int tower1, int tower2, int size)
{
    int i;
    if (tower2 > tower1)
    {
        for (i = 0 ; i < GAP*(tower2-tower1) ; i++)
        {
            gotoxy(GAP*tower1 - size - 2 + i, TOP_PADDING - 4);
            printf("%c", 0);
            gotoxy(GAP*tower1 - size - 2 + 2*(size+2)+1 + i, TOP_PADDING - 4);
            printf("%c", 176);
            Sleep(MOVE_SPEED);
        }
    }
    else
    {
        for (i = 0 ; i > GAP*(tower2-tower1) ; i--)
        {
            gotoxy(GAP*tower1 + size + 2 + i, TOP_PADDING - 4);
            printf("%c", 0);
            gotoxy(GAP*tower1 + size + 2 - 2*(size+2)-1 + i, TOP_PADDING - 4);
            printf("%c", 176);
            Sleep(MOVE_SPEED);
        }
    }
    gotoxy(0, TOP_PADDING + (TOWER_HEIGHT) + 4);
}

void color (int x)
{
  SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),x) ;
}
