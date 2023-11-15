#include "shell.h"

/**
 * tokenize - Tokenize input string into arguments
 * @input: Input string to tokenize
 * @argv: Array to store the arguments
 * Return: Number of arguments
 */
int tokenize(char *input, char *argv[])
{
    // Parse the command and its arguments
    // char *argv[MAX_INPUT_LENGTH];
    int argc = 0;
    char *token = NULL;
    char *saveptr = NULL;

    token = strtok_r((char *)input, " ", &saveptr);

    while (token != NULL && argc < MAX_ARGS - 1)
    {
        argv[argc++] = token;
        token = strtok_r(NULL, " ", &saveptr);
    }

    argv[argc] = NULL; // Null-terminate the arguments array

    return argc;
}
