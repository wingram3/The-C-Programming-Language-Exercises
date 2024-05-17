#include <stdio.h>
#include <string.h>

#define MAXSIZE 1000

/* Write a functio reverse(s) that reverses the character
   string s. Use it to write a program that reverses its input
   a line at a time. */

int my_getline(char s[], int lim);
void reverse(char s[]);


int main(void)
{
    int len;
    char line[MAXSIZE];

    while ((len = my_getline(line, MAXSIZE)) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}


/* reverse: swaps the characters from the beginning and end of string as it works towards the middle. */
void reverse(char s[])
{
    int i, j;
    char temp;

   /* It is -2 to ignore the \n character. */
   for (i = 0, j = strlen(s) - 2; i < j; ++i, --j) {
       temp = s[i];
       s[i] = s[j];
       s[j] = temp;
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
