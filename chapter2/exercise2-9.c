#include <stdio.h>

/* Write a faster version of bitcount with the observation that x &= (x-1)
   deletes the rightmost 1-bit in x for a 2's complement number system. */

int bitcount(unsigned x);

int main(void)
{
    unsigned int x = 0b011010;
    int result;
    result = bitcount(x);
    printf("%d\n", result);
    return 0;
}


/* bitcount: counts the number of 1-bits in x */
int bitcount(unsigned int x)
{
    int b = 0;
    while (x) {
        x &= (x - 1);
        b++;
    }
    return b;
}
