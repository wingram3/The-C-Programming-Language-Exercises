#include <stdio.h>

/* Write a program to count blanks, tabs, and newlines. */

int main(void)
{
    int c;
    int blanks, tabs , newlines;

    blanks = 0;
    tabs = 0;
    newlines = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            ++blanks;

        else if (c == '\t')
            ++tabs;

        else if (c == '\n')
            ++newlines;
    }
    printf("blanks: %d\n", blanks);
    printf("tabs: %d\n", tabs);
    printf("newlines: %d\n", newlines);
    return 0;
}
