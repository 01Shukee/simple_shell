#include "shell.h"

/**
 * alias_list - initialize and return an empty alias list
 *
 * Return: Pointer to the head of the alias list
 */
alias_t *alias_list(void)
{
    return NULL;
}

/**
 * add_node_alias - add a new alias node to the list
 * @head: Pointer to the head of the alias list
 * @alias: Alias to add
 * @command: Actual command equivalent to the alias
 *
 * Return: Pointer to the newly added node or NULL on failure
 */
alias_t *add_node_alias(alias_t **head, char *alias, char *command)
{
    alias_t *new_node, *temp;

    new_node = malloc(sizeof(alias_t));
    if (new_node == NULL)
        return NULL;

    new_node->alias = _strdup(alias);
    new_node->command = _strdup(command);
    new_node->next = NULL;

    if (!*head)
        *head = new_node;
    else
    {
        temp = *head;

        while (temp->next)
            temp = temp->next;

        temp->next = new_node;
    }

    return new_node;
}

/**
 * modify_node_alias - modify an existing alias node
 * @head: Pointer to the head of the alias list
 * @new_var: Alias to modify
 * @new_val: New string to be modified to the found node
 *
 * Return: EXT_SUCCESS on success, EXT_FAILURE on failure
 */
int modify_node_alias(alias_t **head, char *new_var, char *new_val)
{
    alias_t *temp;

    temp = *head;

    while (temp)
    {
        if (_strcmp(temp->alias, new_var) == 0)
        {
            free(temp->command);
            temp->command = _strdup(new_val);

            return EXT_SUCCESS;
        }
        temp = temp->next;
    }

    return EXT_FAILURE;
}

/**
 * remove_node_alias - remove a node from the alias list
 * @head: Pointer to the head of the alias list
 * @var: Alias of the node to be removed
 *
 * Return: EXT_SUCCESS on success, EXT_FAILURE on failure
 */
int remove_node_alias(alias_t **head, char *var)
{
    alias_t *copy_head = *head, *temp = *head;

    if (head == NULL)
        return EXT_FAILURE;

    copy_head = NULL;
    while (temp)
    {
        if (_strcmp(temp->alias, var) == 0)
        {
            if (copy_head)
                copy_head->next = temp->next;
            else
                *head = temp->next;

            free(temp->alias);
            free(temp->command);
            free(temp);

            return EXT_SUCCESS;
        }
        copy_head = temp;
        temp = temp->next;
    }

    return EXT_FAILURE;
}

/**
 * write_alias - write the alias list to stdout for testing
 * @head: Pointer to the head of the alias list
 *
 * Return: Number of characters written
 */
int write_alias(alias_t *head)
{
    int i = 0;
    alias_t *temp = head;

    while (temp)
    {
        write(STDOUT_FILENO, temp->alias, _strlen(temp->alias));
        write(STDOUT_FILENO, "=\"", 2);
        write(STDOUT_FILENO, temp->command, _strlen(temp->command));
        write(STDOUT_FILENO, "\"\n", 2);

        temp = temp->next;
        i++;
    }

    return i;
}