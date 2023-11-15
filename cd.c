#include "shell.h"

int cd(char *directory)
{
    char *homeDir = getenv("HOME");
    char *oldPwd = getenv("PWD");
    char *newPwd;

    if (directory == NULL || strcmp(directory, "~") == 0)
    {
        directory = homeDir;
    }
    else if (strcmp(directory, "~") == 0)
    {
        if (oldPwd == NULL)
        {
            my_print("Error: OLDPWD not set.\n");
            return (-1);
        }
        directory = oldPwd;
    }

    if (chdir(directory) != 0)
    {
        perror("chdir");
        return (-1);
    }

    // update the environ variable PWD
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
