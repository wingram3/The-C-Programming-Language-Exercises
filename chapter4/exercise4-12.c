#include <stdio.h>
#define MAXLEN 1000

/* Adapt the idea of printd to write a recursive version of itoa();
   that is, convert an integer into a string by calling a recursive routine. */

void rec_itoa(int n, char s[], int *i);

int main(void)
{
    static int number = -78567;
    char number_string[MAXLEN];
    int i = 0;
    rec_itoa(number, number_string, &i);
    printf("%s\n", number_string);
    return 0;
}


void rec_itoa(int n, char s[], int *i)
{
    if (n < 0) {
        s[(*i)++] = '-';
        n = -n;
    }
    if (n / 10)
        rec_itoa(n/10, s, i);
    s[(*i)++] = n % 10 + '0';
}
