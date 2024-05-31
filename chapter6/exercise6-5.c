/* Write a function undef that will remove a name and definition
   from the table maintained by lookup and install. */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {      /* table entry */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name        */
    char *defn;             /* replacement text    */
};

struct nlist *install(char *, char *);
void undef(char *name, char *defn);
unsigned hash(char *);
struct nlist *lookup(char *);

static struct nlist *hashtab[HASHSIZE];    /* pointer table */

/* populate hash table */
int main(void)
{
    install("name1", "definition1");
    install("name2", "definition2");
    install("name3", "definition3");

    struct nlist *entry;

    entry = lookup("name1");
    if (entry != NULL)
        printf("name1: %s\n", entry->defn);

    entry = lookup("name2");
    if (entry != NULL)
        printf("name2: %s\n", entry->defn);

    entry = lookup("name3");
    if (entry != NULL)
        printf("name3: %s\n", entry->defn);

    undef("name1", "definition1");
    undef("name2", "definition2");
    undef("name3", "definition3");

    entry = lookup("name1");
    if (entry != NULL)
        printf("name1: %s\n", entry->defn);
    else
        printf("not found.\n");

    entry = lookup("name2");
    if (entry != NULL)
        printf("name2: %s\n", entry->defn);
    else
        printf("not found.\n");

    entry = lookup("name3");
    if (entry != NULL)
        printf("name3: %s\n", entry->defn);
    else
        printf("not found.\n");

    return 0;
}


/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    char *my_strdup(const char *);
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = my_strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);
    if ((np->defn = my_strdup(defn)) == NULL)
        return NULL;
    return np;
}


/* undef: remove (name, defn) from hashtab */
void undef(char *name, char *defn)
{
    struct nlist *np, *prev;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval], prev = NULL; np != NULL; prev = np, np = np->next)
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL)
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
}


/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}


/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
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
