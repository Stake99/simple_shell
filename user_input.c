#include "shell.h"

void read_command(char *input, size_t size)
{
    if (fgets(input, size, stdin) == NULL)
    {
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
    input[strcspn(input, "\n")] = '\0'; // Remove newline
}

// #include "shell.h"

// void read_command(char *command, size_t size) {
//     if (fgets(command, size, stdin) == NULL) {
//         if (feof(stdin)) {
//             leo_print("\n");
//             exit(EXIT_SUCCESS);
//         } else {
//             leo_print("Error while reading input.\n");
//             exit(EXIT_FAILURE);
//         }
//     }
//     command[strcspn(command, "\n")] = '\0'; // Remove newline
// }
