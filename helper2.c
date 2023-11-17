#include "shell.h"

/**
 * help_history - Display information about the history command.
 */
void help_history(void)
{
    _puts("\nUsage: $ history");
    _puts("Display the history list.");
}

/**
 * help_setenv - Display information about the setenv command.
 */
void help_setenv(void)
{
    _puts("\nUsage: $ setenv [NAME] [VALUE]");
    _puts("\tSets a new environmental variable");
}

/**
 * help_unsetenv - Display information about the unsetenv command.
 */
void help_unsetenv(void)
{
    _puts("\nUsage: $ unsetenv [NAME]");
    _puts("\tUnsets a saved environmental variable");
}