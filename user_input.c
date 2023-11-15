#include "shell.h"

/**
 * read_command - Read a command from the standard input
 * @input: Buffer to store the input command
 * @size: Size of the input buffer
 */
void read_command(char *input, size_t size)
{
    // Read input from standard input using fgets
    if (fgets(input, size, stdin) == NULL)
    {
        // Check for end-of-file
        if (feof(stdin))
        {
            my_print("\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            my_print("Error while reading input.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Remove newline character from the input
    input[strcspn(input, "\n")] = '\0';
}
