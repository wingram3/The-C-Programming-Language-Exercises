/* Write getfloat, the floating-point analog of getint. */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 1000
#define SIZE    10

int getch(void);
void ungetch(int c);


/* fills an array of integers by calls to getint */
int main(void)
{
    int n, getfloat(float *);
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;
    return 0;
}


/* getint: get next integer from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    float power;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');   /* integer part */
    if (c == '.')
            c = getch();
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');   /* fractional part */
        power *= 10.0;
    }
    *pn *= sign / power;
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


/* getline: read a line into s, return length  */
int my_getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i<lim-1 && ((c=getchar()) != EOF) && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
