/* Rewrite getline, itoa using pointers. */

#include <stdio.h>
#define STRSIZE 100

int my_getline(char *s, int lim);
void rec_itoa(int n, char s[], int *i);

int main(void)
{
    char str1[STRSIZE];
    int len;

    while ((len = my_getline(str1, STRSIZE)) > 0) {
        printf("%s\n", str1);
    }
    return 0;
}


/* my_getline: read a line into s, return length (pointer version) */
int my_getline(char *s, int lim)
{
    int c;
    char *bs = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - bs;
}


/* rec_itoa: recursive itoa using pointers */
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
