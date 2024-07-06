#include <stdio.h>
#include <stdbool.h>

/* up_or_down: determine if the stack grows up or down.
   Uses recursion so optimization can't mess things up. */
bool up_or_down(int *other)
{
    int x;
    return (!other) ? up_or_down(&x) : &x > other;
}

int main(void)
{
    printf("%s\n", up_or_down(NULL) ? "Up" : "Down");
    return 0;
}
