#include "shell.h"

/**
 * my_print - Print a message to the standard output
 * @message: Message to print
 */
void my_print(const char *message)
{
    // Use the write system call to print the message to standard output
    write(STDOUT_FILENO, message, strlen(message));
}
