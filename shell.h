#ifndef SHELL_H
#define SHELL_H
/*
 *The kjxjhcjxh
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
 *thebse aibfbskf
 */
void display_prompt(void);
void my_print(const char *message);
void custom_execute(char *input, int *success);
//void custom_execute(const char *input);
void read_command(char *input, size_t size);
int tokenize(char *input, char *argv[]);
int cd(char *directory);
int my_setenv(char *variable, char *value);
int my_unsetenv(char *variable);

#endif /* SHELL_H */
