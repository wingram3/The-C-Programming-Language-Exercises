/* Write versions of the library functions strncpy, strncat, and strncmp,
   which operate on at most the first n characters of their argument strings. */

#include <stdio.h>
#define STRSIZE 100

void my_strncpy(char *s, char *t, int n);
void my_strncat(char *s, char *t, int n);
int my_strncmp(char *s, char *t, int n);

int main(void)
{
    char str1[STRSIZE];
    char str2[STRSIZE] = "Ingram";
    my_strncpy(str1, str2, 4);
    printf("%s\n", str1);

    char str3[STRSIZE] = "Will ";
    char str4[STRSIZE] = "Ingram";
    my_strncat(str3, str4, 3);
    printf("%s\n", str3);

    int status;
    char str5[STRSIZE] = "onethree";
    char str6[STRSIZE] = "onetwo";
    status = my_strncmp(str5, str6, 4);
    printf("%d\n", status);

    return 0;
}


/* my_strncpy: copies at most n characters of t to s. */
void my_strncpy(char *s, char *t, int n)
{
    char *bs = s;
    while ((*s++ = *t++) && s < bs+n)
        ;
}


/* my_strncat: copies at most n characters from t to end of s. */
void my_strncat(char *s, char *t, int n)
{
    char *bs;
    while (*++s)
        ;
    bs = s;
    while ((*s++ = *t++) && s < bs+n)
        ;
}


/* my_strncmp: return 0 if first n chars of t match first n chars of s, etc. */
int my_strncmp(char *s, char *t, int n)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0' || --n <= 0)
            return 0;
    return *s - *t;
}
