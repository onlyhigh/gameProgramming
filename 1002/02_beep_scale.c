#include <stdio.h>
#include <math.h>
#include <windows.h>

int calc_frequency(int octave, int inx);

int main(void)
{
    int index[8] = {0, 2, 4, 5, 7, 9, 11, 12};
    int freq[8];
    int i;

    for (i = 0; i < 8; i++)
    {
        freq[i] = calc_frequency(4, index[i]);
    }

    for (i = 0; i < 8; i++)
    {
        Beep(freq[i], 500);
    }

    Sleep(1000);

    for (i = 7; i >= 0; i--)
    {
        Beep(freq[i], 500);
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
