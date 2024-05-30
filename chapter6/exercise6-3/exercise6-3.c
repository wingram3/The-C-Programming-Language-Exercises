/* Write a cross-referencer that prints a list of all words in a document, and,
   for each word, a list of the line numbers on which it occurs. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 1000
#define MAXLEN  1000
#define MAXSTOR 1000
#define INITIAL_LINES_CAPACITY 1000

struct tnode {
    char *word;             /* pointer to the word text                    */
    int *lines;             /* an array of lines on which the word occurs  */
    int lines_lim;          /* capacity of the lines array                 */
    int lines_count;        /* current count of elements in lines          */
    struct tnode *left;     /* left child                                  */
    struct tnode *right;    /* right child                                 */
};

int getword(char *, int, int *);
int readlines(char *lineptr[], char *linestor, int maxlines);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
void freetree(struct tnode *);
struct tnode *talloc(void);

int main(void)
{
    struct tnode *root;
    char word[MAXWORD];
    int line_number = 1;

    root = NULL;
    while (getword(word, MAXWORD, &line_number) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word, line_number);
    treeprint(root);
    freetree(root);
    return 0;
}


struct tnode *talloc(void);
char *my_strdup(char *);

/* addtree: add a new node to the word tree */
struct tnode *addtree(struct tnode *p, char *word, int line)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(word);
        p->lines = (int *)malloc(INITIAL_LINES_CAPACITY * sizeof(int));
        p->lines[0] = line;
        p->lines_lim = INITIAL_LINES_CAPACITY;
        p->lines_count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(word, p->word)) == 0) {
        if (p->lines_count >= p->lines_lim) {
            p->lines_lim *= 2;
            p->lines = (int *)realloc(p->lines, p->lines_lim * sizeof(int));
        }
        p->lines[p->lines_count++] = line;
    }
    else if (cond < 0)
        p->left = addtree(p->left, word, line);
    else
        p->right = addtree(p->right, word, line);
    return p;
}


/* treeprint: in-order print of tree */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%-20s", p->word);
        for (i = 0; i < p->lines_count; i++)
            printf("%d ", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}


/* freetree: free the memory allocated for the binary tree. */
void freetree(struct tnode *p)
{
    if (p != NULL) {
        freetree(p->left);
        freetree(p->right);
        free(p->word);
        free(p->lines);
        free(p);
    }
}


/* talloc: make a tnode. */
struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}


/* strdup: make a duplicate of s. */
char *my_strdup(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}


/* getword: get next word or character from input. */
int getword(char *word, int lim, int *line_number)
{
    int c;
    size_t i = 0;

    while (isspace(c = getc(stdin)))
        if (c == '\n')
            (*line_number)++;

    if (c != EOF)
        word[i++] = c;
    if (!isalpha(c) && c != '_') {
        word[i] = '\0';
        return c;
    }
    while ((isalnum(c = getc(stdin)) || c == '_') && i < lim)
        word[i++] = c;
    if (c == '\n')
        line_number++;
    ungetc(c, stdin);
    word[i] = '\0';
    return word[0];
}
