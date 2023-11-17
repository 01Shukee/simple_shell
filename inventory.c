#include "shell.h"

/**
 * buildarginv - Builds a struct for the arguments inventory.
 * Return: Pointer to arguments inventory struct.
 */
arg_inventory_t *buildarginv(void)
{
    arg_inventory_t *arginv = safe_malloc(sizeof(arg_inventory_t));

    arginv->input_commands = safe_malloc(BUFSIZE * sizeof(char));
    arginv->envlist = env_list();
    arginv->buflimit = BUFSIZE;
    arginv->st_mode = _filemode(STDIN_FILENO);
    arginv->last_bg_pid = -1;
    arginv->n_bg_jobs = 0;
    arginv->exit = 0;
    arginv->exit_status = 0;

    /* Initialize history and history file */
    arginv->history_file = set_name(arginv->envlist, "/.simple_shell_history");
    arginv->history = history_list(arginv);

    /* Initialize aliases and alias file */
    arginv->alias_file = set_name(arginv->envlist, "/.simple_shell_alias");
    arginv->alias = alias_list();
    load_alias(arginv);

    return arginv;
}

/**
 * set_name - Appends home directory absolute path to the filename.
 * @envlist: Linked list of environment variables.
 * @name: The name of the file.
 *
 * Return: Char pointer to the filename.
 */
char *set_name(env_t *envlist, char *name)
{
    char *file, *home;
    int lenhome, lenname;
    env_t *home_node;

    home_node = fetch_node(envlist, "HOME");
    home = home_node->val;

    lenhome = _strlen(home);
    lenname = _strlen(name);

    file = safe_malloc(sizeof(char) * (lenhome + lenname + 1));
    file = _strncat(_strncat(file, home, lenhome), name, lenname);

    return file;
}