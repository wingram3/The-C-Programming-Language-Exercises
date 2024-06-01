/* Modify the pattern finding program of chapter 5 to take its input from a set of named files
   or, if no files are named as arguments, from the standard input. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int my_getline(char *, int, FILE *);
void removedq(const char *, char *);


/* find: print lines from files that match pattern from the first command line argument. */
int main(int argc, char *argv[])
{
    char line[MAXLINE], noquotes[MAXLINE];
    int found = 0;
    FILE *fp;

    if (argc < 2)
        printf("Usage: ./exercise7-7 \"pattern\" [file1] [file2] [...]");
    else if (argc == 2)
        while (my_getline(line, MAXLINE, stdin) > 0) {
            removedq(argv[1], noquotes);
            if (strstr(line, noquotes) != NULL) {
                printf("stdin: %s", line);
                found++;
            }
        }
    else {
        char **files = argv;
        for (int i = 2; i < argc; i++) {
            if ((fp = fopen(files[i], "r")) == NULL) {
                fprintf(stderr, "error: can't open file %s\n", files[i]);
                continue;
            }
            while (my_getline(line, MAXLINE, fp) > 0) {
                removedq(argv[1], noquotes);
                if (strstr(line, noquotes) != NULL) {
                    printf("%s: %s", files[i], line);
                    found++;
                }
            }
        }
    }
    return found;
}


/* my_getline: read a line, return length */
int my_getline(char *line, int max, FILE *fp)
{
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
        return strlen(line);
}


/* removedq: remove double quotes from a string */
void removedq(const char *s, char *p)
{
    int len = strlen(s);

    if (len > 1 && s[0] == '\"' && s[len-1] == '\"') {
        strncpy(p, s+1, len-2);
        p[len-2] = '\0';
    } else
        strcpy(p, s);
}
