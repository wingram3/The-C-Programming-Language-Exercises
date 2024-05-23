/* As written, getint treats + or - not followed by a digit as a valid
   representation of zero. Fix it to push such a character back on the input. */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 1000
#define SIZE    10

int getch(void);
void ungetch(int c);


/* fills an array of integers by calls to getint */
int main(void)
{
    int n, array[SIZE], getint(int *);

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    return 0;
}


/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, d, sign;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        d = c;
        if (!isdigit(c = getch())) {
            if (c != EOF)
                ungetch(c);
            ungetch(d);
            return d;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}


char buf[BUFSIZE];
int bufp = 0;

/* getch: get a (possibly pushed back) character. */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* ungetch: push character back on input. */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}
