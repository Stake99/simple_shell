#ifndef SHELL_H
#define SHELL_H

/*
 * Header file for the shell program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 120
#define MAX_ARGS 10
#define MAX_ALIAS_COUNT 10

extern char **environ;

extern int lastExitStatus;

/*
 * Display the shell prompt
 */
void display_prompt(void);

/*
 * Print a message to the standard output
 */
void my_print(const char *message);

/*
 * Execute a custom command
 * @input: Input command
 * @success: Pointer to the success flag
 */
void custom_execute(char *input, int *success);

/*
 * Read a command from the standard input
 * @input: Buffer to store the input command
 * @size: Size of the input buffer
 */
void read_command(char *input, size_t size);

/*
 * Tokenize an input command into an array of arguments
 * @input: Input command
 * @argv: Array to store the arguments
 * Return: Number of arguments
 */
int tokenize(char *input, char *argv[]);

/*
 * Change the current working directory
 * @directory: Target directory to change to
 * Return: 0 on success, -1 on failure
 */
int cd(char *directory);

/*
 * Set an environment variable
 * @variable: Name of the variable
 * @value: Value to set
 * Return: 0 on success, -1 on failure
 */
int my_setenv(char *variable, char *value);

/*
 * Unset an environment variable
 * @variable: Name of the variable to unset
 * Return: 0 on success, -1 on failure
 */
int my_unsetenv(char *variable);

#endif /* SHELL_H */
