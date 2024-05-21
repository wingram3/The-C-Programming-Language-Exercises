#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLEN 1000

/* Extend atof to handle scientfic notation of the form 123.46e-6. */

double atof(char s[]);
int my_getline(char s[], int lim);

int main(void)
{
    char line[MAXLEN];
    int len;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        printf("%f\n", atof(line));
    }
    return 0;
}


/* atof: convert string s to double. */
double atof(char s[])
{
    double val, power, exponent_val;
    int i, sign, exponent_sign;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        exponent_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exponent_val = 0.0; isdigit(s[i]); i++) {
            exponent_val = 10.0 * exponent_val + (s[i] - '0');
        exponent_val *= exponent_sign;
        if (exponent_val != 0)
            val *= pow(10, exponent_val);
        }
    }
    return val;
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
