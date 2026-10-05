    int index[8] = {0, 2, 4, 5, 7, 9, 11, 12};
    int freq[8];
    int code;
    int i;

    for (i = 0; i < 8; i++)
    {
        freq[i] = calc_frequency(4, index[i]);
    }

    do
    {
        code = getch();

        if ('1' <= code && code <= '8')
        {
            code = code - 49;
            Beep(freq[code], 300);
        }

    } while (code != 27);
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
