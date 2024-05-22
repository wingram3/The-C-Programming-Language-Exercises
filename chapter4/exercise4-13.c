#include <stdio.h>
#include <string.h>

/* Wrtie a recursive version of the function reverse(s),
   which reverses a string in place. */

void reverse(char s[]);


int main(void)
{
    char str[] = "william.";
    reverse(str);
    printf("%s\n", str);
    return 0;
}


void reverse(char s[])
{
    void reverser(char s[], int i, int len);
    reverser(s, 0, strlen(s));
}


void reverser(char s[], int i, int len)
{
    int temp, j;

    j = len - (i + 1);
    if (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        reverser(s, ++i, len);
    }
}
