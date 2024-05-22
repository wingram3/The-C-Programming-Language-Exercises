#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP   100  /* max size of operator or operand */
#define NUMBER  '0'  /* signal that a number was found */
#define MAXVAL  100  /* maximum depth of val stack */
#define BUFSIZE 100

/* Modify the getop so it doesn't need to use ungetch(). Use an interal static variable. */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);


/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: division by zero.\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: division by zero with (modulo operator).\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command.\n");
            break;
        }
    }
    return 0;
}


int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: value stack full, can't push.\n");
}


/* pop: pop a value off of the value stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: value stack empty.\n");
        return 0.0;
    }
}


/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    static char buf[BUFSIZE];
    static int bufp = 0;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.')
            s[++i] = c;
        else {
            if (c != EOF)
                buf[bufp++] = c;
            return '-';
        }
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        buf[bufp++] = c;
    return NUMBER;
}


char buf[BUFSIZE];
int bufp = 0;

/* getch: get a (possibly pushed back) character. */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
