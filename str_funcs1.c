#include "my_shell.h"

/**
 * my_strncat - concatenates from src string to dest string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to concatenate
 *
 * Return: pointer to destination
 */
char *my_strncat(char *dest, char *src, int n)
{
    int i = 0, j = 0;

    while (dest[i] != '\0')
        i++;

    while (j < n && src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';

    return dest;
}

/**
 * my_strcmp - compares string
 * @s1: first string
 * @s2: second string
 *
 * Return: difference between two ASCII values
 */
int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (TRUE)
    {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];

        if (s1[i] == '\0' || s2[i] == '\0')
            break;

        i++;
    }

    return 0;
}

/**
 * my_strlen - finds and returns the length of the string
 * @str: string to find length
 *
 * Return: length of string
 */
unsigned int my_strlen(const char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;

    return i;
}

/**
 * my_strdup - takes a string and copies it to another memory location
 * @str: string to copy
 *
 * Return: pointer to copied string
 */
char *my_strdup(char *str)
{
    unsigned int len, j;
    char *ptrstring;

    if (str == NULL)
        return NULL;

    len = my_strlen(str);

    ptrstring = safe_malloc((len + 1) * sizeof(char));

    for (j = 0; j < len; j++)
        ptrstring[j] = str[j];
    ptrstring[j] = '\0';

    return ptrstring;
}

/**
 * my_strncmp - checks if 2 strings are of equal value and length
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: difference of first chars of different value or 0 on success
 */
int my_strncmp(char *s1, char *s2, unsigned int n)
{
    unsigned int j;

    for (j = 0; j < n; j++)
        if (s1[j] != s2[j])
            return s1[j] - s2[j];

    return 0;
}