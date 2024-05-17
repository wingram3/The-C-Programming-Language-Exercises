#include <stdio.h>
#define TABLEN 4
#define MAXLEN 1000

/* Write a program entab that replaces string of blanks by the mininum number
   of tabs and blanks to achieve the same spacing. */

void entab(char s[]);
int my_getline(char s[], int lim);


int main(void)
{
    char line[MAXLEN];
    int len;

    while ((len = my_getline(line, MAXLEN)) > 0)
        entab(line);
    return 0;
}


void entab(char s[])
{
    int c;
    unsigned int col = 0;
    unsigned int blanks = 0;

    while ((c = getchar()) != EOF) {
        ++col;
        if (c == ' ') {
            ++blanks;
            if (col % TABLEN == 0 && blanks > 1) {
                putchar('\t');
                blanks = 0;
            }
        }
        else {
            while (blanks) {
                putchar(' ');
                --blanks;
            }
            if (c == '\n')
                col = 0;
            putchar(c);
        }
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
