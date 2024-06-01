/* Write a program to compare two files, printing the first line where they differ. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int filecmp(const char *, const char *);

int main(int argc, char *argv[])
{
    int result;
    char *file1, *file2;

    if (argc != 3)
        fprintf(stderr, "Usage: ./exercise7-6 file1 file2\n");
    else {
        file1 = argv[1];
        file2 = argv[2];
        result = filecmp(file1, file2);
    }
    return 0;
}


/* filecmp: compare the lines of two files */
int filecmp(const char *file1, const char *file2)
{
    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr, "error opening file");
        return -1;
    }

    char line1[MAXLINE];
    char line2[MAXLINE];
    int line_number = 1;
    int result = 0;

    while (fgets(line1, MAXLINE, fp1) != NULL) {
        if (fgets(line2, MAXLINE, fp2) != NULL) {
            line1[strcspn(line1, "\n")] = '\0';
            line2[strcspn(line2, "\n")] = '\0';

            if (strcmp(line1, line2) != 0) {
                fprintf(stdout, "Difference found at line %d:\n", line_number);
                fprintf(stdout, "File1: %s\n", line1);
                fprintf(stdout, "File2: %s\n", line2);
                result = 1;
                return result;
            }
        } else {
            fprintf(stdout, "Additional line in File1 at line %d: %s\n", line_number, line1);
            result = 1;
            return result;
        }
        line_number++;
    }

    while (fgets(line2, MAXLINE, fp2) != NULL) {
        fprintf(stdout, "Additional line in File2 at line %d: %s\n", line_number, line2);
        result = 1;
        line_number++;
    }

    fclose(fp1);
    fclose(fp2);
    return result;
}
