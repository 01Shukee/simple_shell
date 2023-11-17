#include "my_shell.h"

/**
 * custom_getline - reads input from standard input
 * @buffer: address of pointer to input commands buffer
 * @limit: max size of input character string, realloc if necessary
 *
 * Return: number of characters read
 */
ssize_t custom_getline(char **buffer, size_t *limit)
{
    ssize_t count;

    count = custom_readline(STDIN_FILENO, buffer, limit);

    return count;
}

/**
 * custom_readline - reads input from a file descriptor
 * @fd: file descriptor to read from
 * @buffer: address of pointer to input commands buffer
 * @limit: max size of input character string, realloc if necessary
 *
 * Return: number of characters read
 */
ssize_t custom_readline(int fd, char **buffer, size_t *limit)
{
    size_t charcount = 0;
    size_t iterations = 1;
    size_t j = 0;
    ssize_t i = -1;

    while (i != 0)
    {
        i = read(fd, (*buffer + j), 1);

        if (i <= 0)
            break;

        charcount++;

        if ((*buffer + j++)[0] == '\n')
            break;

        if (charcount % *limit == 0)
        {
            iterations++;
            *buffer = _realloc(*buffer, charcount, (*limit * iterations));
        }
    }

    return (ssize_t)charcount;
}

/**
 * file_mode - determines the file mode of standard input
 * @fd: file descriptor, typically STDIN_FILENO
 *
 * Return: 1 if a device like a terminal, 0 if a FIFO special file or a pipe
 */
int file_mode(int fd)
{
    int result = -1;
    struct stat buf;

    fstat(fd, &buf);

    switch (buf.st_mode & S_IFMT)
    {
    case S_IFCHR:
        result = 1; // Device like a terminal
        break;
    case S_IFIFO:
        result = 0; // FIFO special file or a pipe
        break;
    default:
        break;
    }

    return result;
}