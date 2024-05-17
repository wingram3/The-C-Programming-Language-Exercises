#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP 20

int main(void)
{
    for (int fahr = UPPER; fahr >= LOWER-1; fahr -= STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    return 0;
}
