/* Modify the sort program to handle a -r flag, which indicates sorting in reverse
   (decreasing) order. Be sure that -r works with -n. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 100
#define MAXSTOR  100
#define NUMERIC  1
#define DECR     2

char *lineptr[MAXLINES];

int my_getline(char *s, int lim);
int readlines(char *lineptr[], char *linestor, int maxlines);
void writelines(char *lineptr[], int nlines, int decr);
void reverse(void *s);

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);

static char option = 0;

/* sort input lines. */
int main(int argc, char **argv)
{
    int nlines;
    int c, rc = 0;
    char linestor[MAXSTOR];

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                option |= NUMERIC;
                break;
            case 'r':
                option |= DECR;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 1;
                rc = -1;
                break;
            }
        }
    }
    if (argc)
        printf("Usage: sort -nr \n");
    else {
        if ((nlines = readlines(lineptr, linestor, MAXLINES)) > 0) {
            if (option & NUMERIC)
                my_qsort((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) numcmp);
            else
                my_qsort((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) strcmp);
            writelines(lineptr, nlines, option & DECR);
        } else {
            printf("input too big to sort.\n");
            rc = -1;
        }
    }
    return rc;
}


/* qsort: sort v[left]...v[right] into increasing order. */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++left, i);
    }
    swap(v, left, last);
    my_qsort(v, left, last-1, comp);
    my_qsort(v, last+1, right, comp);
}


/* numcmp: compare s1 and s2 numerically. */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}


/* swap: exchange two pointers. */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


/* readlines: read input lines */
int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLINES];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

    nlines = 0;
    while ((len = my_getline(line, MAXLINES)) > 0) {
        if (nlines >= maxlines || p+len > linestop)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int decr)
{
    int i;

    if (decr)
        for (i = nlines-1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        while (--nlines >= 0)
            printf("%s\n", *lineptr++);
}


/* my_getline: read a line into s, return length (pointer version) */
int my_getline(char *s, int lim)
{
    int c;
    char *bs = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - bs;
}
