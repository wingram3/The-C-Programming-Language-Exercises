/* Rewrite the routines day_of_year and month_day wioth pointers instead of indexing. */

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
    int m, d;
    int doy, md;

    doy = day_of_year(1988, 3, 21);
    month_day(1988, 60, &m, &d);

    printf("month: %d, day: %d\n", m, d);
    printf("day of year: %d\n", doy);

    return 0;
}


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month and day. */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%100 == 0;
    p = daytab[leap];
    while (--month)
        day += *++p;
    return day;
}


/* month_day: set month, day from day of year. */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%100 == 0;
    p = daytab[leap];
    while (yearday > *++p)
        yearday -= *p;
    *pmonth = p - *(daytab + leap);
    *pday = yearday;
}
