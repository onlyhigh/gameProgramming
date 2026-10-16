
#include <stdio.h>

void reverse_number(long number)
{
    while (number > 0)
    {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}

int main(void)
{
    long number;

    printf("금액을 입력하고 Enter>");
    scanf("%ld", &number);

    reverse_number(number);

    return 0;
}
