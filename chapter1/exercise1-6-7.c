#include <stdio.h>

int main(void)
{
    // Verify that the expression getchar() != EOF is 0 or 1
    // Run the program and press CTRL+D (Unix)
    printf("Value: %d\n", getchar() != EOF);

    // Print the value of EOF
    printf("EOF: %d\n", EOF);

    return 0;
}
