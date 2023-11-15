#include "shell.h"

/**
 * cd - Change current working directory
 * @directory: Target directory to change to
 *
 * Return: 0 on success, -1 on failure
 */
int cd(char *directory)
{
    char *homeDir = getenv("HOME");
    char *oldPwd = getenv("PWD");
    char *newPwd;

    // If directory is NULL or "~", set it to the home directory
    if (directory == NULL || strcmp(directory, "~") == 0)
    {
        directory = homeDir;
    }
    else if (strcmp(directory, "-") == 0)
    {
        // If directory is "-", change to the previous directory
        if (oldPwd == NULL)
        {
            my_print("Error: OLDPWD not set.\n");
            return (-1);
        }
        directory = oldPwd;
    }

    // Change the current working directory
    if (chdir(directory) != 0)
    {
        perror("chdir");
        return (-1);
    }

    // Update the environment variables PWD and OLDPWD
    newPwd = getcwd(NULL, 0);
    if (newPwd == NULL)
    {
        perror("getcwd");
        return (-1);
    }

    my_setenv("PWD", newPwd);
    my_setenv("OLDPWD", oldPwd);

    free(newPwd);

    return (0);
}
