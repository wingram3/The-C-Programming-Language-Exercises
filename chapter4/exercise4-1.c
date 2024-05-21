#include <stdio.h>
#define MAXLEN 1000

/* Write the function strindex(s, t) which returns the position of the rightmost
   occurrence of t in s, or -1 if there is none. */

int strindex(char s[], char t[]);
int my_getline(char s[], int lim);

char pattern[] = "ould";

int main(void)
{
    char line[MAXLEN];
    int found = 0;

    while (my_getline(line, MAXLEN) > 0)
        printf("Rightmost occurence of pattern is at index: %d\n", strindex(line, pattern));
    return 0;
}


/* my_getline: get line into s, return length */
int my_getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}


/* strindex: returns index of rightmost occurence of t is s. */
int strindex(char s[], char t[])
{
    int i, j, k;
    int rightmost = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            rightmost = i;
    }
    return rightmost;
}
