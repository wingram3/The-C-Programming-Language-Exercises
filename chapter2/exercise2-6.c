#include <stdio.h>

/* Write a function getbits(x, p, n, y) that returns x with the n bits that begin
   at position p set to the rightmost n bits of y, leaving the other bits unchanged. */

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void)
{
    unsigned x = 0b10001100;
    unsigned y = 0b11001111;
    unsigned result;

    result = setbits(x, 4, 3, y);
    printf("%d\n", result);
    return 0;
}


unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    ++p;
    unsigned int mask1 = (~(~(~0 << n) << p) & x);
    unsigned int mask2 = (~(~0 << n) & y) << p;
    return mask1 | mask2;
}
