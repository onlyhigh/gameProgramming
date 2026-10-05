#include <stdio.h>
#include <math.h>

void print_frequency(int octave);

int main(void)
{
    int octave;

    printf("Octave frequency table\n\n");

    for (octave = 1; octave <= 6; octave++)
    {
        print_frequency(octave);
    }

    return 0;
}

void print_frequency(int octave)
{
    double do_scale = 32.7032;
    double ratio = pow(2.0, 1.0 / 12.0);
    double temp;
    int i;

    temp = do_scale * pow(2.0, octave - 1);

    printf("Octave %d : ", octave);

    for (i = 0; i < 12; i++)
    {
        printf("%4lu ", (unsigned long)(temp + 0.5));
        temp *= ratio;
    }

    printf("\n");
}
