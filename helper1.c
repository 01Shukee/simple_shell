#include "shell.h"

/**
 * help_alias - Display information about the alias command.
 */
void help_alias(void)
{
    _puts("\nUsage: $ alias [NAME]=[VALUE]");
    _puts("\tDefine or display aliases, in the form:");
    _puts("\n\talias [NAME]=[VALUE]");
}

/**
 * help_cd - Display information about the cd command.
 */
void help_cd(void)
{
    _puts("\nUsage: $ cd");
    _puts("\tChange the shell working directory.");
}

/**
 * help_env - Display information about the env command.
 */
void help_env(void)
{
    _puts("\nUsage: $ env");
    _puts("\tDisplay all environmental variables, in the form:");
    _puts("\n\t[NAME]=[VALUE]");
}

/**
 * help_exit - Display information about the exit command.
 */
void help_exit(void)
{
    _puts("\nUsage: $ exit");
    _puts("\tExit the shell.");
}

/**
 * help_help - Display information about the help command.
 */
void help_help(void)
{
    _puts("\nUsage: $ help [command]");
    _puts("\tDisplay information about builtin commands.");
}