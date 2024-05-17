#include <stdio.h>
#define TABLEN 4
#define MAXLEN 1000

/* Write a program detab that replaces tabs in the input with the proper
   number of spaces. */

void detab(char s[]);
int my_getline(char s[], int lim);


int main(void)
{
    char line[MAXLEN];
    int len;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        detab(line);
    }
    return 0;
}


void detab(char s[])
{
    int c, i;
    c = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (i = 0; i < TABLEN; ++i) {
                putchar(' ');
            }
        }
        else {
            putchar(c);
        }
    }
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
