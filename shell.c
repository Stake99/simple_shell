#include "shell.h"

/**
 * main - Entry point for the shell program
 * @argc: Number of command line arguments
 * @argv: Array of command line arguments
 *
 * Return: 0 on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
    FILE *file = stdin; // Default to stdin
    char input[MAX_INPUT_LENGTH];
    int success = 1;

    // Function prototypes
    int tokenize(char *input, char *argv[]);
    int cd(char *directory);
    int my_setenv(char *variable, char *value);
    int my_unsetenv(char *variable);
    void display_prompt(void);
    void custom_execute(char *input, int *success);

    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2)
    {
        // Open the file if provided as an argument
        file = fopen(argv[1], "r");

        if (file == NULL)
        {
            perror("fopen");
            return EXIT_FAILURE;
        }
    }

    while (true)
    {
        display_prompt();
        read_command(input, sizeof(input));

        // Execute the custom command
        custom_execute(input, &success);

        // Check if the success flag is set
        if (!success)
        {
            printf("Last command failed.\n");
        }
    }

    if (file != stdin)
    {
        // Close the file if opened
        fclose(file);
    }

    return 0;
}
