/* Write a program that prints distinct words in its input sorted into decreasing order
   of frequency of occurence. Precede each word by its count. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD    100
#define NDISTINCT  1000

struct tnode {
    char *word;             /* pointer to text */
    int count;              /* occurence count */
    struct tnode *left;     /* left child      */
    struct tnode *right;    /* right child     */
};

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
void sortlist(void);
void treestore(struct tnode *);
void freetree(struct tnode *);

struct tnode *list[NDISTINCT];      /* pointers to tree nodes */
int ntn = 0;                        /* number of tree nodes   */

/* print distinct words sorted in decreasing order of frequency */
int main(void)
{
    struct tnode *root;
    char word[MAXWORD];
    int i;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treestore(root);
    sortlist();
    for (i = 0; i < ntn; i++)
        printf("%2d:%20s\n", list[i]->count, list[i]->word);

    freetree(root);
    return 0;
}


struct tnode *talloc(void);
char *my_strdup(const char *);

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


/* treestore: store in list[] pointers to tree nodes */
void treestore(struct tnode *p)
{
    if (p != NULL) {
        treestore(p->left);
        if (ntn < NDISTINCT)
            list[ntn++] = p;
        treestore(p->right);
    }
}


/* sortlist: sort list of pointers to tree nodes */
void sortlist(void)
{
    int gap, i, j;
    struct tnode *temp;

    for (gap = ntn/2; gap > 0; gap /= 2)
        for (i = gap; i < ntn; i++)
            for (j = i-gap; j >= 0; j -= gap) {
                if ((list[j]->count) >= (list[j+gap]->count))
                    break;
                temp = list[j];
                list[j] = list[j+gap];
                list[j+gap] = temp;
            }
}


/* getword: get next word or character from input. */
int getword(char *word, int lim)
{
    int c;
    size_t i = 0;

    while (isspace(c = getc(stdin)))
        ;

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
char *my_strdup(const char *s)
{
    char *p;
    size_t len = strlen(s) + 1;

    p = (char *)malloc(len);
    if (p == NULL)
        return NULL;
    strlcpy(p, s, len);
    return p;
}
