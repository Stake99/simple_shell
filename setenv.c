#include "shell.h"

/**
 * my_setenv - Set an environment variable
 * @variable: Name of the variable
 * @value: Value to set
 * Return: 0 on success, -1 on failure
 */
int my_setenv(char *variable, char *value)
{
    // Use setenv to set the environment variable
    if (setenv(variable, value, 1) != 0)
    {
        my_print("Error: setenv.\n");
        return -1;
    }

    return 0;
}
