#include <stdio.h>

/* Wrtie a function invert(x, p, n) that returns x with the n bits that begin
   at position p inverted, leaving the other bits unchanged. */

unsigned invert(unsigned x, int p, int n);

int main(void)
{
    int x = 0b11110000;
    int result;

    result = invert(x, 7, 3);
    printf("%d\n", result);
    return 0;
}


unsigned invert(unsigned x, int p, int n)
{
    unsigned mask = (~(~0 << n)) << (p - n+1);
    return mask ^ x;
}
