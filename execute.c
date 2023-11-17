#include "my_shell.h"

/**
 * is_command_in_path - checks if the input command is in the PATH
 * @command: a command
 *
 * Return: 1 if in PATH, 0 if not
 */
int is_command_in_path(char *command)
{
    int i;

    i = 0;
    while (command[i] != '\0')
    {
        if (command[i] == '/')
            return 1;
        i++;
    }

    return 0;
}

/**
 * execute_builtins - executes built-in commands
 * @arginv: arguments inventory
 *
 * Return: 1 on success, 0 on failure
 */
int execute_builtins(arg_inventory_t *arginv)
{
    int i, retval;
    char *command;
    char **commands;
    builtins_t builtins_list[] = {
        {"env", my_env}, {"setenv", my_setenv},
        {"unsetenv", my_unsetenv}, {"history", my_history}, {"cd", my_cd},
        {"alias", my_alias}, {"unalias", my_unalias}, {"help", my_shell_help},
        {"exit", my_shell_exit},
        {NULL, NULL}
    };

    retval = EXT_FAILURE;
    commands = (char **)arginv->commands;

    for (i = 0; builtins_list[i].command != NULL; i++)
    {
        command = builtins_list[i].command;
        if (_strcmp(command, commands[0]) == 0)
        {
            retval = builtins_list[i].builtin_func(arginv);
            break;
        }
    }

    arginv->exit_status = retval;
    return retval;
}

/**
 * handle_execution_error - frees resources and exits on execution error
 * @msg: error message
 * @command: command to free
 * @environ: environment variables to free
 * @arginv: arguments inventory to free
 */
void handle_execution_error(char *msg, char *command, char **environ, arg_inventory_t *arginv)
{
    delete_pipeline(&arginv->pipeline);
    delete_parser(&arginv->parser);
    delete_tokens(&arginv->tokens);
    free(command);
    free_paths(environ);
    freeall(arginv);
    _perror(msg);
    exit(1);
}

/**
 * execute_command_in_path - executes a command from the PATH
 * @command: command to execute
 * @arginv: arguments inventory
 *
 * Return: parent process id
 */
pid_t execute_command_in_path(char *command, arg_inventory_t *arginv)
{
    pid_t pid;
    char **environ;

    pid = fork();
    if (pid < 0)
    {
        _perror("Critical error: unable to fork()!\n");
        exit(1);
    }

    if (pid == 0)
    {
        environ = link_to_dpointer(arginv->envlist);

        if (execve(command, (char **)arginv->commands, environ) < 0)
            handle_execution_error("No Command\n", command, environ, arginv);
    }

    free(command);
    return pid;
}

/**
 * execute_command - executes the input command
 * @arginv: arguments inventory
 *
 * Return: process id of the parent
 */
pid_t execute_command(arg_inventory_t *arginv)
{
    env_t *envlist;
    char **commands;
    char *path, *command;
    char **paths;

    envlist = arginv->envlist;
    commands = (char **)arginv->commands;

    command = safe_malloc(sizeof(char) * BUFSIZE);
    command = _strcpy(command, *commands);

    if (execute_builtins(arginv) == EXT_FAILURE)
    {
        if (is_command_in_path(command))
        {
            return execute_command_in_path(command, arginv);
        }
        else
        {
            path = safe_malloc(sizeof(char) * BUFSIZE);
            locate_path(path, envlist);
            paths = tokenize_path(path);
            cat_path(paths, command);
            free_paths(paths);
            free(path);
            return execute_command_in_path(command, arginv);
        }
    }

    free(command);
    return -1;
}