#include <stdio.h>

int main(void)
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Celsius    Fahr.\n");
    printf("----------------\n");

    fahr = lower;
    while (fahr <= upper)
    {
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%5.1f %9.0f\n", celsius, fahr);
        fahr += step;
    }
}
