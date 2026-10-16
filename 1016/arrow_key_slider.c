
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y);
void draw_rectangle(int c, int r);
void draw_horizontal_slide(int x, int y, int length, const char *s);
void draw_vertical_slide(int x, int y, int length, const char *s);
void move_arrow_key(int key, int *x, int *y, int x_b, int y_b);

int main(void)
{
    const char *slide = "■";
    int key;
    int x = 1, y = 1;
    int h_slide_length, v_slide_length;

    SetConsoleOutputCP(CP_UTF8);

    printf("슬라이드바 표시\n\n");

    printf("수평 슬라이드바 길이(1~70)> ");
    if (scanf("%d", &h_slide_length) != 1)
        return 1;

    printf("수직 슬라이드바 길이(1~19)> ");
    if (scanf("%d", &v_slide_length) != 1)
        return 1;

    if (h_slide_length < 1 || h_slide_length > 70 ||
        v_slide_length < 1 || v_slide_length > 19)
    {
        printf("입력 범위를 확인하세요.\n");
        return 1;
    }

    system("cls");

    do
    {
        draw_vertical_slide(1, y, v_slide_length, slide);
        draw_horizontal_slide(x, v_slide_length + 3,
                              h_slide_length, slide);

        key = _getch();

        if (key == 0 || key == 224)
            key = _getch();

        move_arrow_key(key, &x, &y,
                       h_slide_length, v_slide_length);

    } while (key != 27);

    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw_rectangle(int c, int r)
{
    int i, j;

    printf("┌");
    for (i = 0; i < c; i++)
        printf("──");
    printf("┐\n");

    for (i = 0; i < r; i++)
    {
        printf("│");
        for (j = 0; j < c; j++)
            printf("  ");
        printf("│\n");
    }

    printf("└");
    for (i = 0; i < c; i++)
        printf("──");
    printf("┘\n");
}

void draw_horizontal_slide(int x, int y, int length, const char *s)
{
    int real_length = length / 2;

    gotoxy(1, y);
    draw_rectangle(real_length + 1, 1);

    gotoxy(x + 2, y + 1);
    printf("%s", s);

    gotoxy(real_length * 2 + 6, y);
    printf("%2d", x);
}

void draw_vertical_slide(int x, int y, int length, const char *s)
{
    gotoxy(x, 1);
    draw_rectangle(1, length);

    gotoxy(x + 2, y + 1);
    printf("%s", s);

    gotoxy(x + 6, length + 1);
    printf("%2d", y);
}

void move_arrow_key(int key, int *x, int *y, int x_b, int y_b)
{
    switch (key)
    {
        case 72:
            if (*y > 1) (*y)--;
            break;

        case 75:
            if (*x > 1) (*x)--;
            break;

        case 77:
            if (*x < x_b) (*x)++;
            break;

        case 80:
            if (*y < y_b) (*y)++;
            break;
    }
}
