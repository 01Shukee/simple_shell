#include "shell.h"

/**
 * process_execute_core - Core execution function for processes in a pipeline.
 * @arginv: Argument inventory.
 *
 * Return: PID of the last process in the pipeline.
 */
pid_t process_execute_core(arg_inventory_t *arginv)
{
    for (unsigned int i = 0; i < arginv->pipeline.processesN; i++)
    {
        ptree_t *ptree = arginv->pipeline.processes[i].ptree;
        arginv->commands = ptree->strings;
        ptree->stringsN += expand_alias(arginv);
        ptree->strings = arginv->commands;
        arginv->pipeline.processes[i].pid = execute(arginv);
    }
    return arginv->pipeline.processes[arginv->pipeline.processesN - 1].pid;
}

/**
 * process_execute_tree - Recursively executes a parsing tree.
 * @arginv: Argument inventory.
 * @ptree: Parsing tree.
 * @depth: Depth of the parsing tree.
 *
 * Return: PID of the last process executed.
 */
pid_t process_execute_tree(arg_inventory_t *arginv, ptree_t *ptree, unsigned int depth)
{
    if (!ptree)
        return -1;

    int status = 0;
    int id = ptree->token_id;

    if (id == TOKEN_STRING || id == TOKEN_PIPE || is_redirection(id))
    {
        init_pipeline(&arginv->pipeline, ptree);
        pid_t last_pid = process_execute_core(arginv);
        delete_pipeline(&arginv->pipeline);
        return last_pid;
    }

    if (ptree->left)
    {
        pid_t last_pid = process_execute_tree(arginv, ptree->left, depth + 1);

        if (id != TOKEN_BACKGROUND)
        {
            waitpid(last_pid, &status, 0);
            status = WEXITSTATUS(status);
        }
        else
        {
            arginv->n_bg_jobs++;
            arginv->last_bg_pid = last_pid;
        }

        arginv->exit_status = (status == 1) ? 127 : status;

        if ((id == TOKEN_AND && status) || (id == TOKEN_OR && !status))
            return last_pid;

        return process_execute_tree(arginv, ptree->right, depth + 1);
    }

    return -1;
}

/**
 * process_execute - Executes processes based on the parsing tree.
 * @arginv: Argument inventory.
 *
 * Return: Always returns 0.
 */
int process_execute(arg_inventory_t *arginv)
{
    pid_t last_pid = process_execute_tree(arginv, arginv->parser.tree, 0);
    int status = 0;

    if (last_pid != -1)
    {
        if (arginv->parser.tree->token_id != TOKEN_BACKGROUND)
        {
            waitpid(last_pid, &status, 0);
            status = WEXITSTATUS(status);
        }
        else
        {
            arginv->n_bg_jobs++;
            arginv->last_bg_pid = last_pid;
        }

        arginv->exit_status = (status == 1) ? 127 : status;
    }

    return 0;
}