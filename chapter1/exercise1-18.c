#include <stdio.h>

#define MAXSIZE 1000

/* Write a program to remove trailing blanks and tabs from
   each line of input, and to delete entirely blank lines. */

int remove_trail(char line[]);
int my_getline(char s[], int lim);


int main(void)
{
    int len;
    char line[MAXSIZE];

    while ((len = my_getline(line, MAXSIZE)) != EOF) {
        if (remove_trail(line) > 0)
            printf("%s", line);
    }
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
    s[i] = '\0';
    return i;
}


/* Go backwards through the string and remove whitespace. */
int remove_trail(char line[])
{
    int i;

    for (i = 0; line[i] != '\n'; ++i);
    --i;

    for (i=i; ((line[i] == ' ') || (line[i] == '\t')); --i);

    if (i >= 0) {
        ++i;
        line[i] = '\n';
        ++i;
        line[i] = '\0';
    }
    return i;
}
