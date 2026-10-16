
#include <stdio.h>
#include <math.h>

void serial_number(long number)
{
    long num;
    int i, length = 0;

    length = (int)(log10(number) + 1);

    for (i = length; i >= 1; i--)
    {
        num = number / (long)pow(10, i - 1);
        printf("%ld\n", num);

        number = number - num * (long)pow(10, i - 1);
    }

    printf("\n");
}

int main(void)
{
    long number;

    printf("금액을 입력하고 Enter>");
    scanf("%ld", &number);

    if (number > 0)
        serial_number(number);

    return 0;
}
