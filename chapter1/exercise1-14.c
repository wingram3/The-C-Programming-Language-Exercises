#include <stdio.h>

/* Write a program to print a histogram of
   the frequencies of different characters in the input. */

int main(void)
{
    int c;
    int frequencies[128];

    for (int i = 0; i < 128; ++i)
        frequencies[i] = 0;

    while ((c = getchar()) != EOF)
        frequencies[c]++;

    // Print the histogram
    for (int i = 0; i < 128; ++i)
    {
        for (int j = 0; j < frequencies[i]; ++j)
             printf("#");
        printf("\n");
    }
    return 0;
}
