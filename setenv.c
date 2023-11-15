#include "shell.h"

int my_setenv(char *variable, char *value)
{
    if (setenv(variable, value, 1) != 0)
    {
        my_print("Error: setenv.\n");
        return (-1);
    }

    return (0);
}
