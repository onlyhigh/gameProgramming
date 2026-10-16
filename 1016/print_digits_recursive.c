
#include <stdio.h>

void serial_number(long number);

int main(void)
{
    long number = 123;

    printf("입력 숫자 : %ld\n\n", number);

    printf("높은 단위부터 출력\n");
    serial_number(number);

    return 0;
}

void serial_number(long number)
{
    if (number > 0)
    {
        serial_number(number / 10);
        printf("%ld\n", number % 10);
    }
    else
        return;
}
