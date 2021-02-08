#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <readline/readline.h>

#define FIRST_PROMPT "Enter double as bits with space seperated sign, exponent, and fraction.\n" \
                     "The fraction does not have to be specified in full length. everything after the\n" \
                     "last entered character will be assumed to be 0's\n" \
                     "Example: 0 10000000011 111101...\n\n"

#define REPEAT_PROMPT "Spacing: _ ___________ ____________________________________________________\n" \
                      "Input:   "


/**
 * Checks that a string is only 1's and 0's
 */
bool is_bitstring(char *str)
{
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    return true;
}


int main()
{
    char sign, exponent[12], fraction[53], buf[65], *line;
    printf(FIRST_PROMPT);

    while ((line = readline(REPEAT_PROMPT)) != NULL)
    {   
        int ret = sscanf(line, "%c %11s %52s", &sign, exponent, fraction);

        if (ret != 3 || strlen(exponent) != 11) {
            fprintf(stderr, "Exponent must be specified in full!\n");
            rl_free(line);
            continue;
        }

        bool valid_strs = is_bitstring(exponent) && is_bitstring(fraction);

        if (!valid_strs || (sign != '0' && sign != '1')) {
            fprintf(stderr, "Input must be only 1's and 0's!\n");
            rl_free(line);
            continue;
        }

        // build one string to shove into memory
        buf[0] = sign;
        buf[1] = '\0';
        strcat(buf, exponent);
        strcat(buf, fraction);

        unsigned long storage = 0;

        int len = strlen(buf);
        for (int i = 0;  i < len; ++i) {
            if (buf[i] == '1') {
                storage |= 1l << (63 - i);
            }
        }

        printf("%lf\n", *(double *) &storage);
        rl_free(line);
    }

    return EXIT_SUCCESS;
}
