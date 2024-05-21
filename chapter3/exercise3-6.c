#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

/* Write a version of itoa() that takes three arguments instead of two.
   The third argument is a minimum field width; the converted number must
   be padded with blanks to the left if necessary to make it wide enough. */

void reverse(char s[]);
void itoa(int n, char s[], int padding);
void reverse(char s[]);
int ilen(int a);


int main(void)
{
    int number = -785;
    char number_string[MAXLEN];
    itoa(number, number_string, 6);
    printf("%s\n", number_string);
    return 0;
}


int ilen(int a)
{
    int i = 0;
    do {
        ++i;
    } while(a /= 10);
    return i;
}


void itoa(int n, char s[], int padding)
{
    int i, j, sign;
    sign = n;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);

    if (sign < 0)
        s[i++] = '-';

    int len = ilen(sign);
    while (len < padding) {
        s[i++] = ' ';
        --padding;
    }
    s[i] = '\0';
    reverse(s);
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
