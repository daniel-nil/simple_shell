#include "main.h"

/**
 * sh_buffer - memory allocator
 * @b_size: memory parameter
 * Return: address
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
 * sh_exbuffer - size of memory expander
 * @b_size: memory parameter
 * @b: pointer
 * Return: address
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
 * sh_checkempty - line pass checker
 * @len: length of string
 * @b: pointer
 * Return: address
 */
int sh_checkempty(ssize_t len, char *b)
{
	return (len == 0 || (len == 1 && b[0] == '\n'));
}

/**
 * sh_handleempty - checks line passed
 * @lptr: doublepointer
 * @b: pointer
 * Return: -1
 */
int sh_handleempty(char *b, char **lptr)
{
	free(b);
	*lptr = NULL;
	return (-1);
}

/**
 * sh_terminator - terminate buffer
 * @len: length of string
 * @b: pointer
 */
void sh_terminator(ssize_t len, char *b)
{
	b[len] = '\0';
}
