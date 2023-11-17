#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: Pointer to reallocate memory.
 * @old_size: Size in bytes of allocated memory.
 * @new_size: New size of memory block in bytes.
 *
 * Return: Void pointer to the new allocation of memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    unsigned int i;

    if (ptr == NULL)
        return safe_malloc(new_size);

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (old_size == new_size)
        return ptr;

    new_ptr = safe_malloc(new_size);

    for (i = 0; i < old_size && i < new_size; i++)
        new_ptr[i] = ((char *)ptr)[i];

    free(ptr);

    return new_ptr;
}

/**
 * mem_reset - Sets all bytes of a string to '\0'.
 * @str: String.
 * @bytes: Number of bytes.
 *
 * Return: Pointer to the string with reset memory.
 */
char *mem_reset(char *str, int bytes)
{
    int i = 0;

    while (i < bytes)
        str[i++] = '\0';

    return str;
}

/**
 * safe_malloc - Mallocs memory of size bytes, prints an error message on error.
 * @bytes: Number of bytes to malloc.
 *
 * Return: Pointer to malloced memory or NULL.
 */
void *safe_malloc(int bytes)
{
    void *check = malloc(bytes);

    if (check == NULL)
    {
        _perror("No Memory\n");
        exit(1);
    }

    return mem_reset(check, bytes);
}