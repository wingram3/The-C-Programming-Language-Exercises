/* Write a pointer version of strcat(s, t). It copies the string t
   to the end of the string s. */

#include <stdio.h>
#define STRSIZE 100

void my_strcat_np(char s[], char t[]);
void my_strcat(char *s, char *t);

int main(void)
{
    char str1[STRSIZE] = "Will ";
    char str2[STRSIZE] = "Ingram";

    my_strcat(str1, str2);
    printf("%s\n", str1);

    return 0;
}


/* my_strcat: copies string to t to end of s (pointer version) */
void my_strcat(char *s, char *t)
{
    while (*++s)            /* go to the end of s. */
        ;
    while ((*s++ = *t++))
        ;
}


/* my_strcat_np: copies string to t to end of s (non-pointer version) */
void my_strcat_np(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}
