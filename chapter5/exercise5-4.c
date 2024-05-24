/* Write the function strend(s, t) which returns 1 if the string
   t occurs at the end of the string t, and 0 o/w. */

#include <stdio.h>
#define STRSIZE 100

int strend(char *s, char *t);

int main(void)
{
    int status;
    char str1[STRSIZE] = "befriend";
    char str2[STRSIZE] = "friend";

    status = strend(str1, str2);
    printf("%d\n", status);
    return 0;
}


/* strend: returns 1 if t occurs at end of s, 0 otherwise. Assumes t is shorter than s. */
int strend(char *s, char *t)
{
    char *bs = s;      /* remember beginning of strings.        */
    char *bt = t;

    for (; *s; s++)    /* find the end of s.                    */
        ;
    for (; *t; t++)    /* find the end of t.                    */
        ;
    for (; *s == *t; s--, t--)
        if (t == bt || s == bs)     /* at beginning of a string */
            break;
    if (*s == *t && t == bt && *s != '\0')
        return 1;
    else
        return 0;
}
