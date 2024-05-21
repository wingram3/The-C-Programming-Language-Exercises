#include <stdio.h>
#define MAXLEN 1000

/* Wrtie a function escape(s, t) that converts characters like newline and tab
   into visible escape sequences like \n and \t as it copies the string t to s.
   Use a switch. */

void escape(char s[], char t[]);
int my_getline(char s[], int lim);


int main(void)
{
    char line[MAXLEN], copied[MAXLEN];
    int len;

    while((len = my_getline(line, MAXLEN)) > 0) {
        escape(copied, line);
    }
    return 0;
}


void escape(char s[], char t[])
{
    int c;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '\n':
                printf("%c%c", '\\', 'n');
                break;
            case '\t':
                printf("%c%c", '\\', 't');
                break;
            default:
                printf("%c", c);
                break;
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
