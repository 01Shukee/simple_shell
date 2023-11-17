#include "my_shell.h"  // Replace "shell.h" with your own header file

/**
 * set_alias - builtin function to set an alias
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int set_alias(arg_inventory_t *inventory)
{
    char *input, **combo, **commands;

    commands = (char **)inventory->commands;

    if (commands[1] == NULL)
    {
        write_alias(inventory->alias);
        return EXT_SUCCESS;
    }
    else if (commands[2] != NULL)
    {
        _perror("alias: too many arguments.\n");
        return -1;
    }

    input = commands[1];

    combo = separate_string(input);

    if (modify_node_alias(&inventory->alias, combo[0], combo[1]) == EXT_FAILURE)
        add_node_alias(&inventory->alias, combo[0], combo[1]);

    free(combo[0]);
    free(combo[1]);
    free(combo);
    return EXT_SUCCESS;
}

/**
 * unset_alias - builtin function to unset an alias
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int unset_alias(arg_inventory_t *inventory)
{
    char **commands;

    commands = (char **)inventory->commands;

    if (commands[1] == NULL)
    {
        _perror("unalias: missing arguments.\n");
        return -1;
    }

    if (commands[2] != NULL)
    {
        _perror("unalias: too many arguments.\n");
        return -1;
    }

    if (remove_node_alias(&inventory->alias, commands[1]) == EXT_SUCCESS)
        return EXT_SUCCESS;

    return EXT_FAILURE;
}

/**
 * display_shell_help - prints help commands info based on the input argument
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int display_shell_help(arg_inventory_t *inventory)
{
    char **commands;
    int i = 0, retval = 127;
    bins_t bins[] = {
        {"exit", help_exit}, {"env", help_env},
        {"setenv", help_setenv}, {"unsetenv", help_unsetenv},
        {"history", help_history}, {"cd", help_cd}, {"alias", help_alias},
        {"help", help_help},
        {NULL, NULL}
    };

    commands = (char **)inventory->commands;
    if (commands[2] != NULL)
    {
        _perror("help: too many input commands.\n");
        return retval;
    }

    while (bins[i].function != NULL)
    {
        if (_strcmp(bins[i].function, commands[1]) == 0)
        {
            bins[i].help();
            retval = EXT_SUCCESS;
            break;
        }
        i++;
    }

    return retval;
}

/**
 * exit_shell - sets the exit status to exit the shell
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int exit_shell(arg_inventory_t *inventory)
{
    char **commands;
    int exit_status;

    commands = (char **)inventory->commands;
    if (commands[1] == NULL)
        inventory->exit = 1;
    else if (is_uint(commands[1]))
    {
        exit_status = _atoi(commands[1]);
        inventory->exit = 1;
        inventory->exit_status = exit_status;
    }
    else
        _perror("exit: Illegal number\n");

    return EXT_SUCCESS;
}