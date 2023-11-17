#include "my_shell.h"

/**
 * my_save_alias - saves alias definitions to a file
 * @my_arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int my_save_alias(arg_inventory_t *my_arginv)
{
    alias_t *my_tmp = my_arginv->alias;
    char *my_file, *my_buffer;
    int my_fd;

    my_file = my_arginv->alias_file;

    my_fd = open(my_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(my_fd);

    while (my_tmp)
    {
        my_buffer = (char *)safe_malloc(_strlen(my_tmp->alias) + _strlen(my_tmp->command) + 4);
        _strcpy(my_buffer, my_tmp->alias);
        _strcat(my_buffer, ":");
        _strcat(my_buffer, my_tmp->command);
        _strcat(my_buffer, "\n");
        append_text_to_file(my_file, my_buffer);
        my_tmp = my_tmp->next;
        free(my_buffer);
    }

    return 0;
}

/**
 * my_load_alias - loads alias definitions from a file
 * @my_arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int my_load_alias(arg_inventory_t *my_arginv)
{
    ssize_t my_count;
    size_t my_sz = BUFSIZE;
    char *my_file, *my_buffer, *my_val;
    int my_fd;

    my_file = my_arginv->alias_file;

    my_fd = open(my_file, O_RDONLY);
    if (my_fd == -1)
    {
        free(my_file);
        return 1;
    }
    my_buffer = (char *)safe_malloc(my_sz);
    while ((my_count = _readline(my_fd, &my_buffer, &my_sz)) != 0)
    {
        while (my_buffer[my_count - 1] == '\n')
            my_buffer[my_count - 1] = '\0';
        my_val = my_buffer;
        while (*my_val && *my_val != ':')
            my_val++;
        if (!*my_val)
            break;
        *(my_val++) = '\0';
        add_node_alias(&my_arginv->alias, my_buffer, my_val);
    }
    free(my_buffer);
    close(my_fd);
    return 0;
}

/**
 * my_fetch_node_alias - fetches a node of a given alias
 * @my_head: head of list
 * @my_var: alias to match of the node to fetch
 *
 * Return: fetched node or NULL
 */
alias_t *my_fetch_node_alias(alias_t *my_head, char *my_var)
{
    alias_t *my_tmp;

    my_tmp = my_head;

    while (my_tmp != NULL)
    {
        if (_strcmp(my_tmp->alias, my_var) == 0)
            return my_tmp;

        my_tmp = my_tmp->next;
    }

    return NULL;
}