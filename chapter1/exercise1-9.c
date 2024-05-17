#include <stdio.h>

/* Write a program to copy its input to its output,
   copying each string of one or more blanks by a single blank. */

int main(void)
{
    int c, blank_count;
    blank_count = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            blank_count++;
        else
            blank_count = 0;

        if (blank_count <= 1)
            putchar(c);
    }
    return 0;
}
