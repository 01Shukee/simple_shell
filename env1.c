#include "my_shell.h"

/**
 * my_link_count - counts number of nodes in linked list
 * @head: pointer to head of linked list
 *
 * Return: number of nodes
 */
unsigned int my_link_count(env_t *my_head)
{
    env_t *my_tmp;
    unsigned int my_count;

    my_tmp = my_head;
    my_count = 0;

    while (my_tmp != NULL)
    {
        my_tmp = my_tmp->next;
        my_count++;
    }

    return (my_count);
}

/**
 * my_env_list - creates a linked list of all environ variables
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
env_t *my_env_list(void)
{
    int i;
    env_t *my_head;
    char **my_variable;

    my_head = NULL;
    for (i = 0; environ[i] != NULL; i++)
    {
        my_variable = separate_string(environ[i]);
        if (add_node_env(&my_head, my_variable[0], my_variable[1]) == NULL)
            return (NULL);
        free(my_variable[0]);
        free(my_variable[1]);
        free(my_variable);
    }

    return (my_head);
}

/**
 * my_link_to_dpointer - converts linked list to double pointer
 * @head: head pointer to head of linked list
 *
 * Return: array of pointers, pointing to strings
 */
char **my_link_to_dpointer(env_t *my_head)
{
    int i;
    unsigned int my_count, len1, len2, lennew;
    char **my_dpointer, *my_var, *my_val, *my_new_val;
    env_t *my_tmp;

    my_count = my_link_count(my_head);
    my_dpointer = malloc(sizeof(char *) * (my_count + 1));

    my_tmp = my_head;
    i = 0;
    while (my_tmp != NULL)
    {
        my_var = my_tmp->var;
        my_val = my_tmp->val;
        len1 = my_strlen(my_var);
        len2 = my_strlen(my_val);

        lennew = len1 + len2 + 2;
        my_new_val = safe_malloc(lennew * sizeof(char));

        _strncat(my_new_val, my_var, len1);
        _strncat(my_new_val, "=", 1);
        _strncat(my_new_val, my_val, len2);
        my_dpointer[i] = my_new_val;
        my_tmp = my_tmp->next;
        i++;
    }
    my_dpointer[i] = NULL;

    return (my_dpointer);
}