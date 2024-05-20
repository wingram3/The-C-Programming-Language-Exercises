#include <stdio.h>
#define MAXLEN 1000

/* Write a modified version of the squeeze function that deletes each
   character in s1 that matches any character in s2. */

int my_getline(char line[], int lim);
void squeeze(char s1[], char s2[]);


int main(void)
{
    char s1[MAXLEN], s2[MAXLEN];
    my_getline(s1, MAXLEN);
    my_getline(s2, MAXLEN);
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}


void squeeze(char s1[], char s2[])
{
    int i, j;
    for (i = j = 0; s2[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            s1[j++] = s2[i];
    }
    s1[j] = '\0';
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
