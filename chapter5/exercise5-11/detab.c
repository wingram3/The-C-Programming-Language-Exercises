#include <stdio.h>
#include "settab.c"
#include "tabpos.c"

void detab(char *tab);

int main(int argc, char **argv)
{
    char tab[MAXLINE+1];

    settab(argc, argv, tab);
    detab(tab);                 /* intialize tab stops */
    return 0;                   /* replace blanks with tabs */
}


/* detab: repalce tabs with blanks. */
void detab(char *tab)
{
    int c, pos = 1;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            do
                putchar(' ');
            while (tabpos(pos++, tab) != YES);
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
}
