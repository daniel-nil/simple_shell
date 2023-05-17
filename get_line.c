#include "main.h"
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>


#define BUFFERSIZE 128


/**
 * sh_getline - custom version of getline()
 * @lineptr: buffer for storing strings
 * @n: size of buffer
 * @fd: source to read from
 *
 * Return: -1 or number of char's read
 */
ssize_t sh_getline(char **lineptr, size_t *n, int fd)
{
	ssize_t len = 0;
	size_t buf_size = *n;
	char *buf = *lineptr;
	char c = 0;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (buf == NULL)
	{
		buf_size = BUFFERSIZE;
		buf = sh_buffer(buf_size);
		if (buf == NULL)
		return (-1);
		*lineptr = buf;
	}
	while (read(fd, &c, 1) > 0)
	{
		if (len + 1 >= (ssize_t)buf_size)
		{
			char *newBuf = sh_exbuffer(buf, buf_size);

			if (newBuf == NULL)
			return (-1);
			buf = newBuf;
			*lineptr = buf;
			buf_size *= 2;
		}
		buf[len++] = c;
		if (c == '\n')
			break;
	}
	if (sh_checkempty(len, buf))
		return (sh_handleempty(buf, lineptr));
	sh_terminator(len, buf);
	return (len);
}
