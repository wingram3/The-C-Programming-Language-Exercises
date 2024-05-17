#include <stdio.h>

/* Write a program to print a histogram of the lengths of
   words in its input. */

#define IN  1
#define OUT 2

int main(void)
{
    int c, state, current_length;
    int lengths[11];

    state = OUT;
    for (int i = 0; i < 11; ++i)
        lengths[i] = 0;

    // Get the lengths of each word and store them in the lengths array.
    current_length = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            if (current_length > 10)
                lengths[10]++;
            else
                lengths[current_length]++;
            current_length = 0;
        }

        else if (state == OUT)
            state = IN;

        if (state == IN)
            current_length++;
    }

    for (int i = 0; i < 11; ++i)
        printf("%d", lengths[i]);


    // Print the histogram.
    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < lengths[i]; ++j)
             printf("#");
        printf("\n");
    }
    return 0;
}
