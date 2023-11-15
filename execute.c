#include "shell.h"

/**
 * custom_execute - Execute commands from input
 * @input: Command input string
 * @success: Pointer to success flag
 */
void custom_execute(char *input, int *success)
{
    pid_t child_pid;
    int i, j = 0;
    char *commands[MAX_ARGS];
    int commandCount = 0;
    char *token = strtok(input, "&&||");
    char *path = getenv("PATH");
    char *pathCopy = strdup(path);
    int commandFound = 0;
    int lastExitStatus;

    // Ignore comments (lines starting with '#')
    if (input[0] == '#')
    {
        return;
    }

    // Tokenize the command into individual commands
    while (token != NULL && commandCount < MAX_ARGS - 1)
    {
        commands[commandCount++] = token;
        token = strtok(NULL, "&&||");
    }

    commands[commandCount] = NULL; // Ensure the last element is NULL

    // Execute each command
    for (i = 0; i < commandCount; i++)
    {
        // Trim leading and trailing whitespaces
        char *trimmedCommand = commands[i];
        while (*trimmedCommand == ' ' || *trimmedCommand == '\t')
        {
            trimmedCommand++;
        }

        // Check if the command is not empty
        if (*trimmedCommand != '\0')
        {
            // Tokenize the trimmed command
            char *argv[MAX_ARGS];
            int argc = tokenize(trimmedCommand, argv);

            // Variable replacement for $?
            for (j = 0; j < argc; j++)
            {
                if (strcmp(argv[j], "$?") == 0)
                {
                    char exitStatusStr[10];
                    snprintf(exitStatusStr, sizeof(exitStatusStr), "%d", lastExitStatus);
                    argv[j] = strdup(exitStatusStr);
                }
            }

            // Variable replacement for $$
            for (j = 0; j < argc; j++)
            {
                if (strcmp(argv[j], "$$") == 0)
                {
                    char processIdStr[10];
                    snprintf(processIdStr, sizeof(processIdStr), "%d", getpid());
                    argv[j] = strdup(processIdStr);
                }
            }

            // Check if the command is the exit built-in
            if (strcmp(argv[0], "exit") == 0)
            {
                if (argc > 1)
                {
                    // Convert the argument to an integer for the exit status
                    int exitStatus = atoi(argv[1]);
                    printf("Shell terminated with status %d.\n", exitStatus);
                    exit(exitStatus);
                }
                else
                {
                    // No exit status specified, exit with the default status
                    printf("Shell terminated.\n");
                    exit(EXIT_SUCCESS);
                }
            }

            // Check if the command is the env built-in
            if (strcmp(argv[0], "env") == 0)
            {
                // Print the current environment
                char **env = environ;

                while (*env != NULL)
                {
                    printf("%s\n", *env);
                    env++;
                }

                continue;
            }

            // Check if the command is the setenv built-in
            if (strcmp(argv[0], "setenv") == 0)
            {
                if (argc == 3)
                {
                    my_setenv(argv[1], argv[2]);
                }
                else
                {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                }
                continue;
            }

            // Check if the command is the unsetenv built-in
            if (strcmp(argv[0], "unsetenv") == 0)
            {
                if (argc == 2)
                {
                    my_unsetenv(argv[1]);
                }
                else
                {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                }
                continue;
            }

            // Check if the command is the cd built-in
            if (strcmp(argv[0], "cd") == 0)
            {
                if (argc > 2)
                {
                    fprintf(stderr, "Usage: cd [DIRECTORY]\n");
                }
                else
                {
                    cd(argc == 2 ? argv[1] : NULL);
                }
                continue;
            }

            // Check if the command is the alias built-in
            if (strcmp(argv[0], "alias") == 0)
            {
                // Handle alias commands
                if (argc == 1)
                {
                    // Print all aliases
                    // TODO: Implement printing all aliases
                    printf("List all aliases here.\n");
                }
                else
                {
                    // Define or print specific aliases
                    // TODO: Implement defining or printing specific aliases
                    printf("Define or print specific aliases here.\n");
                }
                continue;
            }

            // Check if the command exists in the PATH
            if (path == NULL)
            {
                fprintf(stderr, "Error: PATH environment variable not set.\n");
                continue;
            }

            if (pathCopy == NULL)
            {
                perror("strdup");
                exit(EXIT_FAILURE);
            }

            commandFound = 1;
            // Fork a new process
            child_pid = fork();

            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (child_pid == 0)
            {
                // Child process
                // Execute the command with execve
                if (execve(argv[0], argv, environ) == -1)
                {
                    // Handle command not found
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // Parent process
                // Wait for the child to complete
                int status;
                waitpid(child_pid, &status, 0);

                if (WIFEXITED(status))
                {
                    // Child process exited normally
                    lastExitStatus = WEXITSTATUS(status);
                    *success = lastExitStatus == 0;
                }
                else if (WIFSIGNALED(status))
                {
                    // Child process terminated by a signal
                    printf("Child process terminated by signal %d\n", WTERMSIG(status));
                    *success = 0;
                }
            }

            free(pathCopy);

            if (!commandFound)
            {
                fprintf(stderr, "Command not found: %s\n", argv[0]);
                *success = 0;
            }
        }
    }
}
