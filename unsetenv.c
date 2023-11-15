#include "shell.h"

int my_unsetenv(char *variable)
{
    if (unsetenv(variable) != 0)
    {
        my_print("Error: unsetenv.\n");
        return (-1);
    }

    return (0);
}
