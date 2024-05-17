#include <stdio.h>
#define MAXLINE 1000
#define MAXCOL  20

/* Write a program to fold long input lines into two or more shorter lines after the last
   non-blank character that occurs before the n-th column of input. */

void fold(char s[], int n);
int my_getline(char s[], int lim);


int main(void)
{
    char line[MAXLINE];
    int len;

    len = 0;
    while ((len = my_getline(line, MAXLINE)) > 0) {
        fold(line, MAXCOL);
    }
    return 0;
}


/* fold: basically wraps text after a specified limit column. */
void fold(char s[], int n)
{
    int col = 0;
    int last_blank = -1;
    int i = 0;

    while (s[i] != '\0') {
        if (s[i] == ' ' || s[i] == '\t') {
            last_blank = i;
        }
        if (col >= n) {
            if (last_blank == -1) {
                putchar('\n');
                col = 0;
            }
            else {
                s[last_blank] = '\n';
                col = i - last_blank;
                last_blank = -1;
            }
        }
        putchar(s[i]);
        col++;
        i++;
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
