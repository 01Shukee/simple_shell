#include "shell.h"

/**
 * file_path - Constructs the path for the 'cd' command
 * @commands: Array of pointers to commands
 * @envlist: Head of the environment linked list
 *
 * Return: Full file path
 */
char *file_path(char **commands, env_t *envlist)
{
    env_t *fetched_home, *fetched_old;
    int hyphen;
    char *path;

    // Allocate memory for the file path
    path = safe_malloc(1024);

    // Fetch the HOME and OLDPWD values from the environment list
    fetched_home = fetch_node(envlist, "HOME");
    fetched_old = fetch_node(envlist, "OLDPWD");

    // Check if the '-' option is used
    if (commands[1] != NULL)
        hyphen = _strncmp(commands[1], "-", 1);

    // Determine the appropriate path based on conditions
    if (commands[1] == NULL)
        path = _strcpy(path, fetched_home->val);
    else if (hyphen == 0)
        path = _strcpy(path, fetched_old->val);
    else if (commands[1][0] == '/')
        path = _strcpy(path, commands[1]);
    else
    {
        getcwd(path, 1024);
        _strncat(path, "/", 1);
        _strncat(path, commands[1], _strlen(commands[1]));
    }

    return path;
}

/**
 * _cd - Builtin 'cd' function
 * @arginv: Argument inventory
 *
 * Return: 0 if successful, -1 if unsuccessful
 */
int _cd(arg_inventory_t *arginv)
{
    char *path, *oldpwd, *pwd, **commands;
    int check;

    // Allocate memory for oldpwd and pwd
    oldpwd = safe_malloc(1024);
    pwd = safe_malloc(1024);

    // Get the current working directory and store it in oldpwd
    getcwd(oldpwd, 1024);

    // Retrieve commands from the argument inventory
    commands = (char **)arginv->commands;

    // Generate the path to change to
    path = file_path(commands, arginv->envlist);

    // Attempt to change the directory
    check = chdir(path);

    // Handle directory change success or failure
    if (check == -1)
    {
        free(oldpwd);
        free(pwd);
        free(path);
        return 2; // Return code for unsuccessful cd
    }
    else
    {
        // Get the updated current working directory
        getcwd(pwd, 1024);

        // Update PWD and OLDPWD in the environment list
        modify_node_env(&arginv->envlist, "PWD", pwd);
        modify_node_env(&arginv->envlist, "OLDPWD", oldpwd);
    }

    // Free allocated memory
    free(oldpwd);
    free(pwd);
    free(path);

    return 0; // Return code for successful cd
}