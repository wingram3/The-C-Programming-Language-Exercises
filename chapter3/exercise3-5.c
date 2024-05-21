#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

/* Write the function itob(n, s, b) that converts the integer n into a
   base b character representation in the string s. In particular, itob(n, s, 16)
   formats n as a hexadecimal integer in s. */

void itob(int n, char s[], int b);
char itoc(int n);
void reverse(char s[]);


int main(void)
{
    char number_string[MAXLEN];
    int number = 1000;

    itob(number, number_string, 2);
    printf("%s\n", number_string);

    itob(number, number_string, 8);
    printf("%s\n", number_string);

    itob(number, number_string, 16);
    printf("%s\n", number_string);

    return 0;
}


void itob(int n, char s[], int b)
{
    int i = 0, sign = n;

    do {
        s[i++] = itoc(abs(n) % b);
        n /= b;
    } while (n);

    switch (b) {
        case 2:
          s[i++] = 'b';
          s[i++] = '0';
          break;

        case 8:
          s[i++] = 'o';
          s[i++] = '0';
          break;

        case 16:
          s[i++] = 'x';
          s[i++] = '0';
          break;
    }
    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}


char itoc(int n)
{
    if (n <= 9)
        return n + '0';
    return n + 'a' - 10;
}


/* reverse: reverse a string in place. */
void reverse(char s[])
{
    int temp, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
