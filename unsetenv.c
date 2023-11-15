#include "shell.h"

/**
 * my_unsetenv - Unset an environment variable
 * @variable: Name of the variable to unset
 * Return: 0 on success, -1 on failure
 */
int my_unsetenv(char *variable)
{
    // Use unsetenv to remove the environment variable
    if (unsetenv(variable) != 0)
    {
        my_print("Error: unsetenv.\n");
        return -1;
    }

    return 0;
}
