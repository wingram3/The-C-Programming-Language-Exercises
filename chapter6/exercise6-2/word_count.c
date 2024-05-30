#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 10000

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main(void)
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);
    return 0;
}


struct tnode *talloc(void);
char *my_strdup(char *);

/* addtree: add a node with w, at or below p. */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}


/* treeprint: in-order print of tree p. */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
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
