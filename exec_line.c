#include "main.h"

/**
 * sh_buffer - allocates memory
 * @buf_size: memory size
 * Return: allocated memory address
 */

char *sh_buffer(size_t buf_size)
{
	char *buf = (char *) malloc(buf_size);

	if (buf == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (buf);
}

/**
 * sh_exbuffer - increases size of allocated memory
 * @buf_size: memory size
 * @buf: pointer to allocated memory
 * Return: newly allocated memory address
 */
char *sh_exbuffer(char *buf, size_t buf_size)
{
	char *newBuf = (char *) sh_realloc(buf, buf_size);

	buf_size *= 2;
	if (newBuf == NULL)
	{
		free(buf);
		errno = ENOMEM;
		return (NULL);
	}
	return (newBuf);
}

/**
 * sh_checkempty - checks if empty line is passed
 * @len: length of string
 * @buf: pointer to allocated memory
 * Return: newly allocated memory address
 */
int sh_checkempty(ssize_t len, char *buf)
{
	return (len == 0 || (len == 1 && buf[0] == '\n'));
}

/**
 * sh_handleempty - handles empty line passed
 * @lineptr: double pointer
 * @buf: pointer to allocated memory
 * Return: -1
 */
int sh_handleempty(char *buf, char **lineptr)
{
	free(buf);
	*lineptr = NULL;
	return (-1);
}

/**
 * sh_terminator - terminates the buffer
 * @len: length of string
 * @buf: pointer to allocated memory
 */
void sh_terminator(ssize_t len, char *buf)
{
	buf[len] = '\0';
}
