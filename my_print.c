#include "shell.h"

void my_print(const char *message)
{
    write(STDOUT_FILENO, message, strlen(message));
}
