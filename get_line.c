#include "main.h"
#include <stddef.h>


#define BUFFERSIZE 128


/**
 * sh_getline - duplicate getline
 * @lptr: pointer strings
 * @x: size buffer
 * @fd: source
 * Return: -1 or something else
 */
ssize_t sh_getline(char **lptr, size_t *x, int fd)
{
	ssize_t len = 0;
	size_t b_size = *x;
	char *b = *lptr;
	char c = 0;

	if (lptr == NULL || x == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (b == NULL)
	{
		b_size = BUFFERSIZE;
		b = sh_buffer(b_size);
		if (b == NULL)
		return (-1);
		*lptr = b;
	}
	while (read(fd, &c, 1) > 0)
	{
		if (len + 1 >= (ssize_t)b_size)
		{
			char *new_b = sh_exbuffer(b, b_size);

			if (new_b == NULL)
			return (-1);
			b = new_b;
			*lptr = b;
			b_size *= 2;
		}
		b[len++] = c;
		if (c == '\n')
			break;
	}
	if (sh_checkempty(len, b))
		return (sh_handleempty(b, lptr));
	sh_terminator(len, b);
	return (len);
}
