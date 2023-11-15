#include "shell.h"
/*
 *
 */

int main(int argc, char *argv[])
{
    FILE *file = stdin; // Default to stdin
    char input[MAX_INPUT_LENGTH];

    int tokenize(char *input, char *argv[]);
    int cd(char *directory);
    int my_setenv(char *variable, char *value);
    int my_unsetenv(char *variable);
    int success = 1;

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
        // void custom_execute(char *command, int *success);

        custom_execute(input, &success);
        //custom_execute(input);

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
