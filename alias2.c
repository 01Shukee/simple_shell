#include "my_shell.h"  // Replace "shell.h" with your own header file

/**
 * save_my_aliases - saves custom aliases to a file
 * @inventory: arguments inventory
 *
 * Return: 0 on success, 1 on failure
 */
int save_my_aliases(arg_inventory_t *inventory)
{
    alias_t *current_alias = inventory->alias;
    char *file_path, *buffer;
    int fd;

    file_path = inventory->alias_file;

    fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    close(fd);

    while (current_alias)
    {
        buffer = (char *)safe_malloc(_strlen(current_alias->alias) + _strlen(current_alias->command) + 4);
        _strcpy(buffer, current_alias->alias);
        _strcat(buffer, ":");
        _strcat(buffer, current_alias->command);
        _strcat(buffer, "\n");

        append_text_to_file(file_path, buffer);

        current_alias = current_alias->next;
        free(buffer);
    }

    return 0;
}

/**
 * load_my_aliases - loads custom aliases from a file
 * @inventory: arguments inventory
 *
 * Return: 0 on success, 1 on failure
 */
int load_my_aliases(arg_inventory_t *inventory)
{
    ssize_t count;
    size_t buffer_size = BUFSIZE;
    char *file_path, *buffer, *value;
    int fd;

    file_path = inventory->alias_file;

    fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        free(file_path);
        return 1;
    }

    buffer = (char *)safe_malloc(buffer_size);
    while ((count = _readline(fd, &buffer, &buffer_size)) != 0)
    {
        while (buffer[count - 1] == '\n')
            buffer[count - 1] = '\0';

        value = buffer;
        while (*value && *value != ':')
            value++;

        if (!*value)
            break;

        *(value++) = '\0';
        add_node_alias(&inventory->alias, buffer, value);
    }

    free(buffer);
    close(fd);
    return 0;
}

/**
 * find_my_alias_node - fetches a node of a given custom alias
 * @head: head of the alias list
 * @var: alias to match for fetching the node
 *
 * Return: fetched node or NULL
 */
alias_t *find_my_alias_node(alias_t *head, char *var)
{
    alias_t *current_alias = head;

    while (current_alias != NULL)
    {
        if (_strcmp(current_alias->alias, var) == 0)
            return current_alias;

        current_alias = current_alias->next;
    }

    return NULL;
}