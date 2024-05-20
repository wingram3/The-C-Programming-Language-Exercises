#include <stdio.h>

/* Write a function rightrot(x, n) that returns the value of the integer x
   rotated to the right by n positions. */

unsigned rightrot(unsigned x, int n);
int bitcount(unsigned x);

int main(void)
{
    int x = 0b11000000;
    unsigned result;
    result = rightrot(x, 4);
    printf("%d\n", result);
    return 0;
}


unsigned rightrot(unsigned x, int n)
{
    int num_bits = bitcount(x);
    n %= num_bits;
    return (x >> n) | ((x << (num_bits - n)) & ((1 << num_bits) - 1));
}


int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        b++;
    return b;
}
