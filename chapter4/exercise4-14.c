#include <stdio.h>

/* Define a macro swap(t, x, y) that interchanges two arguments of type t. */

#define t int
#define swap(t, x, y)  {    t _z;   \
                            _z = y; \
                            y = x;  \
                            x = _z; }

int main(void)
{
    int x = 0;
    int y = 5;

    printf("%d\n", x);
    printf("%d\n", y);

    swap(t, x, y)

    printf("%d\n", x);
    printf("%d\n", y);

    return 0;
}
