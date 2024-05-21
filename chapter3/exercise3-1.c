#include <stdio.h>
#include <time.h>

#define ITERATIONS 100000
#define MAXLEN     10000

/* Write a version of binary search that makes only one test inside the loop
   (at the price of more tests outside). Compare computation times. */

int binsearch(int x, int v[], int n);
int binsearch_book(int x, int v[], int n);
void test_binsearch(int binsearch(int x, int v[], int n), int x, int v[], int n);
void init_vector(int v[], int n);


int main(void)
{
    int v[MAXLEN];
    init_vector(v, MAXLEN);

    int x = 69;
    test_binsearch(binsearch, x, v, MAXLEN);
    test_binsearch(binsearch_book, x, v, MAXLEN);

    return 0;
}


void init_vector(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}


int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0,
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (x == v[low - 1])
        return low - 1;

    return -1;
}


int binsearch_book(int x, int v[], int n)
{
    int low, high, mid;
    low = 0,
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}


void test_binsearch(int binsearch(int x, int v[], int n), int x, int v[], int n)
{
    static int test_nr = 0;
    long clocks = clock();

    int i;
    for (i = 0; i < ITERATIONS; ++i)
        binsearch(x, v, n);

    clocks = clock() - clocks;
    printf("test_%d: %lu clocks (%.4f seconds)\n", test_nr, clocks, (double)clocks / CLOCKS_PER_SEC);
    ++test_nr;
}
