#include <stdio.h>
#define MAXLEN 1000

/* Write a function expand(s1, s2) that expands shorthand notation like a-z in
   string s1 into the equivalent complete list abc...xyz in s2. Allow for letters
   of either case and digits. */

void expand(const char s1[], char s2[]);
int my_getline(char s[], int lim);

int main(void)
{
    char s1[MAXLEN], s2[MAXLEN];
    int len;

    while ((len = my_getline(s1, MAXLEN)) > 0) {
        expand(s1, s2);
    }
    printf("%s\n", s2);
    return 0;
}


void expand(const char s1[], char s2[])
{
    int i, j = 0;
    char start, end;

    for (i = 0; s1[i] != '\0'; ++i) {
        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0') {
            start = s1[i-1];
            end = s1[i+1];

            if (start < end) {
                for (char c = start + 1; c < end; ++c)
                    s2[j++] = c;
            }
            else if (start > end) {
                for (char c = start - 1; c > end; --c)
                    s2[j++] = c;
            }
        }
        else
            s2[j++] = s1[i];
    }
    s2[j] = '\0';
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
