/* Add commands to print the top element of the stack without popping,
   to duplicate it, and to swap the top two elements. Add a command to
   clear the stack. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP   100  /* max size of operator or operand */
#define NUMBER  '0'  /* signal that a number was found */
#define MAXVAL  100  /* maximum depth of val stack */
#define BUFSIZE 100  /* maximum size of the character buffer */

/* Add the modulus operator and provisions for negative numbers. */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void clear(void);

/* external variables */
int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;


/* reverse Polish calculator */
int main(void)
{
    int type;
    double op1, op2;
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
        case '?':                       /* Print the top element of the stack without popping. */
            op2 = pop();
            printf("\t%.8g\n", op2);
            push(op2);
            break;
        case 'c':                       /* clear the value stack. */
            clear();
            break;
        case 'd':                       /* duplicate the top element of the stack. */
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case 's':                       /* swap the top two elements of the stack. */
            op1 = pop();
            op2 = pop();
            push(op1);
            push(op2);
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}


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
                ungetch(c);
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
        ungetch(c);
    return NUMBER;
}


/* getch: get a (possibly pushed back) character. */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* ungetch: push character back on input. */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}


/* clear: clear the value stack. */
void clear(void)
{
    sp = 0;
}
