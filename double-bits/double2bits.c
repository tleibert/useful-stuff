#include <stdio.h>
#include <stdlib.h>

int main()
{
    double number;
    printf("Enter double to convert: ");
    while (scanf("%lg", &number) == 1) {
        long number_hack = *(long *) &number;
        putchar(number_hack & (1l << 63) ? '1' : '0');
        putchar(' ');

        for (int i = 62; i >= 52; --i) {
            putchar(number_hack & (1l << i) ? '1' : '0');
        }
        putchar(' ');

        for (int i = 51; i >= 0; --i) {
            putchar(number_hack & (1l << i) ? '1' : '0');
        }
        printf("\nEnter double to convert: "); 
    }

    return EXIT_SUCCESS;
}
