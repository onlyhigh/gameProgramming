#include <stdio.h>
#include <math.h>
#include <windows.h>

int calc_frequency(int octave, int inx);

int main(void)
{
    /*
        PDF에는 이 실습의 정확한 음 배열이 제공되지 않았다.
        아래 melody는 "학교 종이 땡땡땡" 연습용으로 재구성한 예제이다.

        0:C  1:D  2:E  3:F  4:G  5:A  6:B  7:high C
    */

    int index[8] = {0, 2, 4, 5, 7, 9, 11, 12};
    int freq[8];

    int melody[] = {
        4, 4, 5, 5, 4, 4, 2,
        4, 4, 2, 2, 1,
        4, 4, 5, 5, 4, 4, 2,
        4, 2, 1, 2, 0
    };

    int length = sizeof(melody) / sizeof(melody[0]);
    int i;

    for (i = 0; i < 8; i++)
    {
        freq[i] = calc_frequency(4, index[i]);
    }

    printf("Playing practice melody...\n");

    for (i = 0; i < length; i++)
    {
        Beep(freq[melody[i]], 300);
        Sleep(80);
    }

    return 0;
}

int calc_frequency(int octave, int inx)
{
    double do_scale = 32.7032;
    double ratio = pow(2.0, 1.0 / 12.0);
    double temp;
    int i;

    temp = do_scale * pow(2.0, octave - 1);

    for (i = 0; i < inx; i++)
    {
        temp *= ratio;
    }

    return (int)(temp + 0.5);
}
