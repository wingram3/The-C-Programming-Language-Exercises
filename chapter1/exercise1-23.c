#include <stdio.h>

#define MAXSTR 10000
#define TRUE   (1 == 1)
#define FALSE  !TRUE

/* Write a program to remove all comments from a C program. (including this one) */
// Test comment

int get_str(char str[], int lim);
void remove_comments(char str[], char no_comm_str[]);


int main(void)
{
    /**
     * Multi
     * line
     * block
     * comment.
    */

    char str[MAXSTR];
    char no_comment_str[MAXSTR];

    get_str(str, MAXSTR);
    remove_comments(str, no_comment_str);
    printf("%s", no_comment_str);

    return 0;
}


int get_str(char str[], int lim)
{
    int c, i = 0;
    while ((i < lim-1 && (c = getchar()) != EOF))
        str[++i] = c;
    str[i] = '\0';
    return i;
}


void remove_comments(char str[], char no_comm_str[])
{
    int in_quote = FALSE;
    int block_comment = FALSE;
    int line_comment = FALSE;

    int i = 0, j = 0;
    while (str[i] != EOF) {
        if (!block_comment) {
            if (!in_quote && str[i] == '"')
                in_quote = TRUE;
            else if (in_quote && str[i] == '"')
                in_quote = FALSE;
        }

        if (!in_quote) {
            if (str[i] == '/' && str[i+1] == '*' && !line_comment)
                block_comment = TRUE;
            if (str[i] == '*' && str[i+1] == '/') {
                block_comment = FALSE;
                i += 2;
            }
            if (str[i] == '/' && str[i+1] == '/')
                line_comment = TRUE;
            if (str[i] == '\n')
                line_comment = FALSE;
            if (line_comment || block_comment)
                ++i;
            else if (!line_comment || !block_comment)
                no_comm_str[j++] = str[i++];
        }
        else
            no_comm_str[j++] = str[i++];
    }
    no_comm_str[j] = '\0';
}
