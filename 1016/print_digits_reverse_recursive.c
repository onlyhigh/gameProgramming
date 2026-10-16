
#include <stdio.h>

void reverse_number(long number);

int main(void)
{
    long number = 123;

    printf("입력 숫자 : %ld\n\n", number);

    printf("낮은 단위부터 출력\n");
    reverse_number(number);

    return 0;
}

void reverse_number(long number)
{
    printf("%ld\n", number % 10);

    if ((number / 10) > 0)
        reverse_number(number / 10);
    else
        return;
}
