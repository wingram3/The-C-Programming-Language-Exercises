/* Rewrite readlines to store lines in an array supplied my main(),
   rather than calling alloc to maintain storage. */

#include <stdatomic.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 1000
#define MAXLEN   1000    /* maximum length of line          */
#define MAXSTOR  5000    /* size of available storage space */

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char *linestor, int nlines);

void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int my_getline(char *, int);

/* sort input lines */
int main(void)
{
    int nlines;
    char linestor[MAXSTOR];

    if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


/* readlines: read input lines */
int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0) {
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
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}


/* qsort: sort v[left]...v[right] into increasing order. */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}


/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
