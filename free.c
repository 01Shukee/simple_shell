#include "my_shell.h"

/**
 * free_all - frees all allocated memory in the argument inventory
 * @arginv: arguments inventory
 *
 * Return: exit status
 */
int free_all(arg_inventory_t *arginv)
{
    int exit_status;

    if (arginv)
    {
        save_alias(arginv);
        file_history(arginv);
        free_history(arginv->history);
        free(arginv->history_file);
        free_environ(arginv->envlist);
        free_alias(arginv->alias);
        free(arginv->alias_file);

        if (arginv->input_commands)
            free(arginv->input_commands);

        exit_status = arginv->exit_status;
        free(arginv);
    }

    return exit_status;
}

/**
 * free_alias - frees all allocated memory for alias linked list
 * @head: head of alias linked list
 *
 * Return: 0 on success, 1 on failure
 */
int free_alias(alias_t *head)
{
    alias_t *temp;

    while (head)
    {
        temp = head->next;
        free(head->alias);
        free(head->command);
        free(head);
        head = temp;
    }

    return EXT_SUCCESS;
}

/**
 * free_environ - frees all allocated memory for environment linked list
 * @head: head of environment linked list
 *
 * Return: 0 on success, 1 on failure
 */
int free_environ(env_t *head)
{
    env_t *temp;

    while (head)
    {
        temp = head->next;
        free(head->var);
        free(head->val);
        free(head);
        head = temp;
    }

    return EXT_SUCCESS;
}

/**
 * free_history - frees all allocated memory for history linked list
 * @head: head of history linked list
 *
 * Return: 0 on success, 1 on failure
 */
int free_history(history_t *head)
{
    history_t *temp;

    while (head)
    {
        temp = head->next;
        free(head->command);
        free(head);
        head = temp;
    }

    return EXT_SUCCESS;
}