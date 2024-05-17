#include <stdio.h>
#define SOMELEN 69

/* Write a loop eqivalent to the for loop (from the previous page in the book)
   without using && and || operators. */

int main(void)
{
    /*
    Orginal for loop:

    for (i = 0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
    */

    int i, c, lim;
    char s[SOMELEN];

    i = 0;
    while (i < lim-1) {
        if ((c = getchar()) != '\n') {
            if (c != EOF) {
                ++i;
                s[i] = c;
            }
            else
                break;
        }
        else
            break;
    }
}
