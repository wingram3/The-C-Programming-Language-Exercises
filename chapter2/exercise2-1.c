#include <limits.h>
#include <stdio.h>

/* Write a program to determine the ranges of char,
   short, int, and long variables, both signed and unsigned. */

int main(void)
{
    // char
    printf("unisgned char range: %d - %d\n", 0, UCHAR_MAX);
    printf("signed char ranges: %d - %d\n", SCHAR_MIN, SCHAR_MAX);

    // int
    printf("unsigned int range: %d - %d\n", 0, UINT_MAX);
    printf("signed int range: %d - %d\n", INT_MIN, INT_MAX);

    // short
    printf("unsigned short range: %d - %d\n", 0, USHRT_MAX);
    printf("signed short range: %d - %d\n", SHRT_MIN, SHRT_MAX);

    // long
    printf("unsigned long range: %d - %ld\n", 0, ULONG_MAX);
    printf("signed long range: %ld - %ld\n", LONG_MIN, LONG_MAX);
}
