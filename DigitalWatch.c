#include <stdio.h>
#include <windows.h>
#include <time.h>

#define CHAR 177

int xPos[6];

void drawNumber(int num, int pos);
void gotoxy(int x, int y);
void clearPos(int pos);

int main()
{
	time_t currentTime = time(0);
	struct tm *now = 0;
	int sec, min, hour, osec, omin, ohour;
	xPos[0] = 5;
	xPos[1] = 9;
	xPos[2] = 15;
	xPos[3] = 19;
	xPos[4] = 25;
	xPos[5] = 29;
	gotoxy(13, 6);
	printf("%c", CHAR);
	gotoxy(13, 8);
	printf("%c", CHAR);
	gotoxy(23, 6);
	printf("%c", CHAR);
	gotoxy(23, 8);
	printf("%c", CHAR);
    time(&currentTime);
    now = localtime(&currentTime);
    ohour = now->tm_hour;
    omin = now->tm_min;
    osec = now->tm_sec;
    drawNumber(ohour/10, 0);
    drawNumber(ohour%10, 1);
    drawNumber(omin/10, 2);
    drawNumber(omin%10, 3);
    drawNumber(osec/10, 4);
    drawNumber(osec%10, 5);
    while (1)
    {
        time(&currentTime);
        now = localtime(&currentTime);
        hour = now->tm_hour;
        min = now->tm_min;
        sec = now->tm_sec;
        if (sec != osec)
        {
            drawNumber(sec/10, 4);
            drawNumber(sec%10, 5);
            osec = sec;
        }
        if (min != omin)
        {
            drawNumber(min/10, 2);
            drawNumber(min%10, 3);
            omin = min;
        }
        if (hour != ohour)
        {
            drawNumber(hour/10, 0);
            drawNumber(hour%10, 1);
            ohour = hour;
        }
    }
	return 0;
}

void drawNumber(int num, int pos)
{
    int i;
    char c = CHAR;
    switch(num)
    {
    case 1:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos], 5 + i);
            printf("%c", c);
        }
        break;
    case 2:
        clearPos(pos);
        gotoxy(xPos[pos], 5);
        printf("%c%c%c", c, c, c);
        gotoxy(xPos[pos] + 2, 6);
        printf("%c", c);
        gotoxy(xPos[pos], 7);
        printf("%c%c%c", c);
        gotoxy(xPos[pos], 8);
        printf("%c", c);
        gotoxy(xPos[pos], 9);
        printf("%c%c%c", c);
        break;

    case 3:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos] + 2, 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 5 ; i+=2)
        {
            gotoxy(xPos[pos], 5+i);
            printf("%c%c", c, c);
        }
        break;
    case 4:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos] + 2, 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 3 ; i++)
        {
            gotoxy(xPos[pos], 5+i);
            printf("%c", c);
        }
        gotoxy(xPos[pos]+1, 7);
        printf("%c",c);
        break;
    case 5:
        clearPos(pos);
        gotoxy(xPos[pos], 5);
        printf("%c%c%c", c, c, c);
        gotoxy(xPos[pos], 6);
        printf("%c", c);
        gotoxy(xPos[pos], 7);
        printf("%c%c%c", c);
        gotoxy(xPos[pos] + 2, 8);
        printf("%c", c);
        gotoxy(xPos[pos], 9);
        printf("%c%c%c", c);
        break;
    case 6:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos], 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 5 ; i+=2)
        {
            gotoxy(xPos[pos]+1, 5+i);
            printf("%c%c", c, c);
        }
        gotoxy(xPos[pos]+2, 8);
        printf("%c", c);
        break;
    case 7:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos] + 2, 5 + i);
            printf("%c", c);
        }
        gotoxy(xPos[pos], 5);
        printf("%c%c", c, c);
        break;

    case 8:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos], 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos] + 2, 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 5 ; i+=2)
        {
            gotoxy(xPos[pos]+1, 5+i);
            printf("%c", c);
        }
        break;
    case 9:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos] + 2, 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 5 ; i+=2)
        {
            gotoxy(xPos[pos], 5+i);
            printf("%c%c", c, c);
        }
        gotoxy(xPos[pos], 6);
        printf("%c", c);
        break;
    case 0:
        clearPos(pos);
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos], 5 + i);
            printf("%c", c);
        }
        for (i = 0 ; i < 5 ; i++)
        {
            gotoxy(xPos[pos] + 2, 5 + i);
            printf("%c", c);
        }
        gotoxy(xPos[pos] + 1, 5);
        printf("%c", c);
        gotoxy(xPos[pos] + 1, 9);
        printf("%c", c);
    }
}

void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearPos(int pos)
{
    int i, j;
    for (i = 0; i < 3 ; i++)
    {
        for (j = 0 ; j < 5 ; j++)
        {
            gotoxy(xPos[pos] + i, 5 + j);
            printf(" ");
        }
    }
}