#include <stdio.h>
#include <conio.h>

int main(void)
{
    int chr;

    do
    {
        chr = getch();

        if (chr == 0 || chr == 0xE0)
        {
            chr = getch();
            printf("Extended key code = %d\n", chr);
        }
        else
        {
            printf("ASCII code = %d\n", chr);
        }
    } while (1);

    return 0;
}
