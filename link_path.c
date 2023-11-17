#include "shell.h"

/**
 * locate_path - Finds the value of the PATH environment variable.
 * @path: Pointer to the path buffer.
 * @envlist: Pointer to the envlist linked list.
 *
 * Return: 1 if found, 0 if not.
 */
int locate_path(char *path, env_t *envlist)
{
    env_t *tmp = envlist;

    while (tmp)
    {
        if (_strcmp(tmp->var, "PATH") == 0)
        {
            _strcpy(path, tmp->val);
            return 1;
        }

        tmp = tmp->next;
    }

    return 0;
}

/**
 * cat_path - Concatenates command to each path to search if it's a valid command.
 * @search_path: Array of paths to search.
 * @cmd: Command to search for.
 *
 * Return: 0 if found, -1 if not found.
 */
int cat_path(char **search_path, char *cmd)
{
    int i;
    char *new;

    new = safe_malloc(BUFSIZE);

    for (i = 0; search_path[i] != NULL; i++)
    {
        _strcpy(new, search_path[i]);
        _strcat(new, "/");
        _strcat(new, cmd);

        if (access(new, F_OK) == 0)
        {
            _strcpy(cmd, new);
            free(new);
            return 0;
        }
        else
        {
            mem_reset(new, BUFSIZE);
        }
    }

    free(new);
    return -1;
}

/**
 * count_paths - Counts how many paths are in the PATH string.
 * @path_str: PATH environment variable.
 *
 * Return: Number of paths found.
 */
int count_paths(char *path_str)
{
    int count = 0;

    if (path_str[0] != '\0')
        count++;

    for (int i = 0; path_str[i]; i++)
    {
        if (path_str[i] == ':')
            count++;
    }

    return count;
}

/**
 * tokenize_path - Tokenizer specifically for PATH.
 * @path_str: PATH environment variable string.
 *
 * Return: Pointer to array of path folders.
 */
char **tokenize_path(char *path_str)
{
    int i = 0, count = 0, start = 0, end;
    char **paths = safe_malloc((count_paths(path_str) + 1) * sizeof(char *));

    while (1)
    {
        if (path_str[i] == ':' || path_str[i] == '\0')
        {
            end = i;

            if (end == start)
                paths[count] = safe_malloc(3 * sizeof(char));
            else
                paths[count] = safe_malloc((end - start + 1) * sizeof(char));

            _strncpy(paths[count], &path_str[start], end - start);
            count++;
            start = i + 1;
        }

        if (path_str[i] == '\0')
            break;

        i++;
    }

    paths[count] = NULL;
    return paths;
}

/**
 * free_paths - Frees the array of paths.
 * @paths: Paths array.
 */
void free_paths(char **paths)
{
    for (int i = 0; paths[i]; i++)
        free(paths[i]);

    free(paths);
}