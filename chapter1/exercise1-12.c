#include <stdio.h>

/* Write a program that prints its input one word per line. */

#define IN  1
#define OUT 0

int main(void)
{
    int c, state;
    state = OUT;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            printf("\n");
        }

        else if (state == OUT)
            state = IN;

        if (state == IN)
            putchar(c);
    }
    return 0;
}
