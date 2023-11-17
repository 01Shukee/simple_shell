#include "shell.h"

/**
 * write_history - Writes all elements of history to file.
 * @head: Head of linked list to print.
 *
 * Return: Number of nodes printed.
 */
unsigned int write_history(history_t *head)
{
	unsigned int i = 0;

	while (head)
	{
		write_uint(head->number);
		write(STDOUT_FILENO, "  ", 2);
		write(STDOUT_FILENO, head->command, _strlen(head->command));
		head = head->next;
		i++;
	}

	return i;
}

/**
 * write_uint - Writes unsigned integers to buffer or stdout in decimal.
 * @n: Unsigned integer to write.
 *
 * Return: Number of characters written to buffer.
 */
int write_uint(unsigned int n)
{
	unsigned int copy, size;
	int nth, chars_written = 0;

	size = 1;
	copy = n;

	if (n < 10)
	{
		_putchar('0' + n);
		return 1;
	}

	while (copy / 10 != 0)
		copy /= 10, size *= 10;

	while (size > 0)
	{
		nth = n / size;
		_putchar('0' + nth);
		n -= nth * size;
		size /= 10;
		chars_written++;
	}

	return chars_written;
}

/**
 * _puts - Prints a string from pointer to string.
 * @str: String to print.
 *
 * Return: void.
 */
void _puts(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
	_putchar('\n');
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return write(STDOUT_FILENO, &c, 1);
}

/**
 * print_list - Prints all elements of a linked list.
 * @head: Head of linked list to print.
 *
 * Return: Number of nodes printed.
 */
size_t print_list(env_t *head)
{
	unsigned int i = 0;
	char **_environ;

	_environ = link_to_dpointer(head);

	while (_environ[i])
	{
		_puts(_environ[i]);
		free(_environ[i]);
		i++;
	}

	free(_environ);
	return i;
}