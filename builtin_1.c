#include "my_shell.h"  // Replace "shell.h" with your own header file

/**
 * display_environment - writes the environment to stdout
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int display_environment(arg_inventory_t *inventory)
{
    env_t *env_list = inventory->env_list;
    char **commands;

    commands = (char **)inventory->commands;

    if (commands[1] != NULL)
    {
        _perror("env: No such file or directory\n");
        return -1;
    }

    print_list(env_list);

    return EXT_SUCCESS;
}

/**
 * display_history - writes history to stdout
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int display_history(arg_inventory_t *inventory)
{
    history_t *history_list = inventory->history_list;

    write_history(history_list);

    return EXT_SUCCESS;
}

/**
 * set_environment_variable - sets a new environmental variable
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int set_environment_variable(arg_inventory_t *inventory)
{
    char **commands, *new_var, *new_val;
    env_t *env_list = inventory->env_list;

    commands = (char **)inventory->commands;

    if (commands[1] == NULL || commands[2] == NULL)
    {
        _perror("setenv: missing parameters.\n");
        return -1;
    }

    if (commands[3] != NULL)
    {
        _perror("setenv: missing value.\n");
        return -1;
    }

    new_var = commands[1];
    new_val = commands[2];

    if (modify_node_env(&env_list, new_var, new_val) == EXT_FAILURE)
    {
        add_node_env(&env_list, new_var, new_val);
    }

    return EXT_SUCCESS;
}

/**
 * unset_environment_variable - unsets an environmental variable
 * @inventory: arguments inventory
 *
 * Return: 0 on success
 */
int unset_environment_variable(arg_inventory_t *inventory)
{
    char **commands;
    env_t *env_list = inventory->env_list;

    commands = (char **)inventory->commands;

    if (commands[1] == NULL)
    {
        _perror("unsetenv: missing parameters.\n");
        return -1;
    }

    if (commands[2] != NULL)
    {
        _perror("unsetenv: too many input commands.\n");
        return -1;
    }

    if (remove_node_env(&env_list, commands[1]))
        return EXT_FAILURE;

    return EXT_SUCCESS;
}