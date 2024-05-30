/* Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but
different somewhere thereafter. Don't count words within strings or comments.
Make 6 a parameter that can be set from the command line. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 10000
#define YES     1
#define NO      0

struct tnode {
    char *word;
    int match;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int, int *);
int compare(char *s, struct tnode *p, int num, int *found);
void treeprint(struct tnode *);
void freetree(struct tnode *p);
int getword(char *, int);
void skip_comments(void);
void skip_strings(void);

/* word frequency count */
int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];
    int found = NO;
    int num;

    num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0]+1) : 6;
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= num)
            root = addtree(root, word, num, &found);
        found = NO;
    }
    treeprint(root);
    freetree(root);
    return 0;
}


struct tnode *talloc(void);
char *my_strdup(char *);

/* addtree: add a node with w, at or below p. */
struct tnode *addtree(struct tnode *p, char *w, int num, int *found)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->match = *found;
        p->left = p->right = NULL;
    } else if ((cond = compare(w, p, num, found)) < 0)
        p->left = addtree(p->left, w, num, found);
    else if (cond > 0)
        p->right = addtree(p->right, w, num, found);
    return p;
}


/* compare: compare words and update p->match */
int compare(char *s, struct tnode *p, int num, int *found)
{
    int i;
    char *t = p->word;

    for (i = 0; *s == *t; i++, s++, t++)
        if (*s == '\0')
            return 0;
    if (i >= num) {
        *found = YES;
        p->match = YES;
    }
    return *s - *t;
}


/* treeprint: in-order print of tree p if p->match == YES. */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        if (p->match)
            printf("%s\n", p->word);
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
int getword(char *word, int lim)
{
    skip_comments();
    skip_strings();

    int c = getc(stdin);
    size_t i = 0;

    if (c != EOF)
        word[i++] = c;
    if (!isalpha(c) && c != '_') {
        word[i] = '\0';
        return c;
    }
    while ((isalnum(c = getc(stdin)) || c == '_') && i < lim)
        word[i++] = c;
    ungetc(c, stdin);
    word[i] = '\0';
    return word[0];
}


/* skip_comments: skip comments that start with "//" and comments like this one. */
void skip_comments(void)
{
    int c = getc(stdin);
    if (c == '/') {
        c = getc(stdin);
        if (c == '/') {
            while ((c = getc(stdin)) != '\n' && c != EOF)
                ;
        } else if (c == '*') {
            while ((c = getc(stdin)) != '*' && c != EOF)
                ;
            c = getc(stdin);
            if (c == '/') {
                ungetc('\n', stdin);
                return;
            }
        }
    }
    ungetc(c, stdin);
}


/* skip_string: skip words within string literals. */
void skip_strings(void)
{
    int c = getc(stdin);
    if (c == '"')
        while ((c = getc(stdin)) != EOF) {
            if (c == '\\') {
                if ((c = getc(stdin)) != EOF)
                    break;
            }
            else if (c == '"')
                break;
        }
    ungetc(c, stdin);
}
