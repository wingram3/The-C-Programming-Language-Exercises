/* Extend entab and detab to accept the shorthand "entab -m +n"
   to mean tab stops every m columns, starting at column n. */

#include <stdio.h>
#include "tabpos.c"
#include "esettab.c"

void entab(char *tab);

/* replace strings of blanks with tabs */
int main(int argc, char **argv)
{
    char tab[MAXLINE+1];

    esettab(argc, argv, tab);
    entab(tab);                 /* intialize tab stops */
    return 0;                   /* replace blanks with tabs */
}


/* entab: replace strings of blanks with tabs and blanks. */
void entab(char *tab)
{
    int c, pos;
    int nb = 0;     /* # of blanks necessary */
    int nt = 0;     /* # of tabs necessary */

    for (pos = 1; (c = getchar()) != EOF; pos++) {
        if (c == ' ') {
            if (tabpos(pos, tab) == NO)
                ++nb;
            else {
                nb = 0;
                ++nt;
            }
        } else {
            for (; nt > 0; nt--)
                putchar('\t');
            if (c == '\t')
                nb = 0;
            else
                for (; nb > 0; nb--)
                    putchar(' ');
            putchar(c);
            if (c == '\n')
                pos = 0;
            else if (c == '\t')
                while (tabpos(pos, tab) != YES)
                    ++pos;
        }
    }
}
