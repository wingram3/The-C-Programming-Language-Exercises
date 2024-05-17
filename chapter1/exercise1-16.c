#include <stdio.h>
#define MAXLINE 1000

/* Revise the main routine of the longest-line program so that it will correctly
   print the length of arbitrarily long input lines, and as much as possible of
   the text. */

int my_getline(char line[], int maxline);
void copy(char to[], const char from[]);


/* Print the longest input line. */
int main(void)
{
    int len, max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = my_getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
        printf("length: %d, string: %s\n", max, longest);
    return 0;
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

    else {
        /* continue to count the length even if it is longer than the max */
        while ((c = getchar() != EOF) && c != '\n') {
            ++i;
        }
        if (c == '\n') {
            s[i] = c;
            ++i;
        }
    }

    s[i] = '\0';
    return i;
}


/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], const char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
