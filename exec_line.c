#include "main.h"

/**
 * sh_buffer - allocates memory
 * @b_size: memory size
 * Return: allocated memory address
 */

char *sh_buffer(size_t b_size)
{
	char *b = (char *) malloc(b_size);

	if (b == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (b);
}

/**
 * sh_exbuffer - increases size of allocated memory
 * @b_size: memory size
 * @b: pointer to allocated memory
 * Return: newly allocated memory address
 */
char *sh_exbuffer(char *b, size_t b_size)
{
	char *new_b = (char *) sh_realloc(b, b_size);

	b_size *= 2;
	if (new_b == NULL)
	{
		free(b);
		errno = ENOMEM;
		return (NULL);
	}
	return (new_b);
}

/**
 * sh_checkempty - checks if empty line is passed
 * @len: length of string
 * @b: pointer to allocated memory
 * Return: newly allocated memory address
 */
int sh_checkempty(ssize_t len, char *b)
{
	return (len == 0 || (len == 1 && b[0] == '\n'));
}

/**
 * sh_handleempty - handles empty line passed
 * @lptr: double pointer
 * @b: pointer to allocated memory
 * Return: -1
 */
int sh_handleempty(char *b, char **lptr)
{
	free(b);
	*lptr = NULL;
	return (-1);
}

/**
 * sh_terminator - terminates the buffer
 * @len: length of string
 * @b: pointer to allocated memory
 */
void sh_terminator(ssize_t len, char *b)
{
	b[len] = '\0';
}
