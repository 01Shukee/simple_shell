#include "my_shell.h"

/**
 * read_text_file - reads a text file and prints it to the POSIX stdout
 * @filename: the file
 * @letters: number of letters to print
 *
 * Return: actual number of letters it could read and print
 */
ssize_t read_text_file(char *filename, size_t letters)
{
    int fd;
    ssize_t letters_read;
    char *buffer;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return 0;

    buffer = malloc(sizeof(char) * letters);
    if (buffer == NULL)
        return 0;

    letters_read = read(fd, buffer, letters);
    if (letters_read == -1)
    {
        free(buffer);
        return 0;
    }

    letters_read = write(STDOUT_FILENO, buffer, letters_read);
    if (letters_read == -1)
    {
        free(buffer);
        return 0;
    }

    free(buffer);

    return (close(fd) == -1 ? -1 : letters_read);
}

/**
 * truncate_text_to_file - truncates a file and writes text content to it
 * @filename: name of the file
 * @text_content: text to be written to the file
 *
 * Return: 1 on success, -1 on failure
 */
int truncate_text_to_file(char *filename, char *text_content)
{
    int fd;
    size_t len;

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1)
        return -1;

    if (text_content == NULL)
        return (close(fd) == -1 ? -1 : 1);

    len = _strlen(text_content);

    if (write(fd, text_content, len) == -1)
    {
        close(fd);
        return -1;
    }

    return (close(fd) == -1 ? -1 : 1);
}

/**
 * append_text_to_file - appends text to the end of a file
 * @filename: name of file to have text appended to
 * @text_content: text to be appended to the file
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(char *filename, char *text_content)
{
    int fd;
    size_t len;

    fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
    if (fd == -1)
        return -1;

    if (text_content == NULL)
        return (close(fd) == -1 ? -1 : 1);

    len = _strlen(text_content);

    if (write(fd, text_content, len) == -1)
    {
        close(fd);
        return -1;
    }

    return (close(fd) == -1 ? -1 : 1);
}