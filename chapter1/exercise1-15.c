#include <stdio.h>

/* Rewrite the temperature conversion program
   to use a function for conversion. */

#define LOWER 0
#define UPPER 300
#define STEP 20

float convert_F_to_C(int fahr);

int main(void)
{
    for (int fahr = LOWER; fahr <= UPPER; fahr += STEP)
        printf("%6.1d %3.2f\n", fahr, convert_F_to_C(fahr));
    return 0;
}

float convert_F_to_C(int ftemp)
{
    float celsius;
    celsius = (5.0/9.0) * (ftemp - 32.0);
    return celsius;
}
