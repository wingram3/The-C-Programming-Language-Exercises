#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXLEN 1000

/* Write a function htoi(s) which converts a string of hex digits
   into its equivalent integer value. Allowable chararacters are
   0-9, a-f, A-F. */

int htoi(char s[]);
int my_getline(char line[], int lim);


int main(void)
{
    char str[MAXLEN];
    my_getline(str, MAXLEN);
    printf("%d\n", htoi(str));
    return 0;
}


int htoi(char s[])
{
    int result = 0;
    int temp, i = 0, len = strlen(s);

    while (i < len) {
        if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X'))
            i += 2;

        temp = tolower(s[i]);
        if (isdigit(temp))
            temp -= 48;
        if (isalpha(temp) && temp <= 'f')
            temp = temp - 'a' + 10;
        if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'))
            result += temp * (int)pow(16, len-i-1);
        else
            printf("Error: Invalid String.");

        ++i;
    }
    return result;
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
