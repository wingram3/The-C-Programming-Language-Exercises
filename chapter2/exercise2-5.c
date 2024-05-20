#include <stdio.h>
#define MAXLEN 1000

/* Write a function any(s1, s2) that returns the first location in the string s1
   where any character from string s2 occurs, or -1 if s1 contains no characters
   from s2. */

int any(char s1[], char s2[]);
int my_getline(char line[], int lim);


int main(void)
{
    int loc;
    char s1[MAXLEN], s2[MAXLEN];

    my_getline(s1, MAXLEN);
    my_getline(s2, MAXLEN);

    loc = any(s1, s2);
    printf("%d\n", loc);

    return 0;
}


int any(char s1[], char s2[])
{
    int i, j;
    for (i = 0; s2[i] != '\0'; i++)
        for (j = 0; s1[j] != '\0'; j++) {
            if (s1[j] == s2[i])
                return j;
        }
    return -1;
}


/* getline: read a line into s, return length  */
int my_getline(char line[], int lim)
{
    char c;
    int i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}
