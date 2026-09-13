#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define X_MAX 79
#define Y_MAX 24

void move_arrow_key(int key, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);

int main(void)
{
    int key;
    int x = 10;
    int y = 5;

    do
    {
        gotoxy(x, y);
        printf("A");

        key = getch();

        if (key == 0 || key == 0xE0)
        {
            key = getch();
            move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
        }
    } while (key != 27);

    return 0;
}

void move_arrow_key(int key, int *x, int *y, int x_b, int y_b)
{
    switch (key)
    {
    case 72:
        *y = *y - 1;
        if (*y < 1) *y = 1;
        break;
    case 75:
        *x = *x - 1;
        if (*x < 1) *x = 1;
        break;
    case 77:
        *x = *x + 1;
        if (*x > x_b) *x = x_b;
        break;
    case 80:
        *y = *y + 1;
        if (*y > y_b) *y = y_b;
        break;
    default:
        break;
    }
}

void gotoxy(int x, int y)
{
    COORD Pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
