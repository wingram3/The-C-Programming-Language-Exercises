#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000

/* Modify the itoa() function to handle the largest negative number. */

void itoa(int n, char s[]);
void reverse(char s[]);
int my_getline(char s[], int lim);

int main(void)
{
    int number = -785;
    char number_string[MAXLEN];
    itoa(number, number_string);
    printf("%s\n", number_string);
    return 0;
}


void itoa(int n, char s[])
{
    int i, sign;
    sign = n;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if (sign < 0)
        s[i++] = '-';
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
