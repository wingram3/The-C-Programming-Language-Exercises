#include <stdio.h>

/* Rewrite the function lower, which converts upper case letters
   to lower case, with a conditional expression instead of if-else. */

int lower(int c);

int main(void)
{
    int result1, result2;
    char letter1 = 'B', letter2 = 'Z';
    result1 = lower(letter1);
    result2 = lower(letter2);
    printf("%c, %c\n", result1, result2);
    return 0;
}


/* lower: converts upper case to lower case, ASCII only */
int lower(int c)
{
    return ((c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : (c));
}
