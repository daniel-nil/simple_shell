#include "main.h"

/**
 * sh_memcpy - copies bytes from memory
 * @dest: a pointer to the destination buffer
 * @src: a pointer to the source buffer
 * @x: the number of bytes to copy.
 * Return: void pointer to the destination buffer.
 */
void *sh_memcpy(void *dest, const void *src, size_t x)
{
	char *a = dest;
	const char *b = src;
	size_t y;

	for (y = 0; y < x; y++)
	{
		a[y] = b[y];
	}
	return (dest);
}

/**
 * sh_realloc - changes size of memory block
 * @p: pointer to the previously allocated memory block
 * @size: new size to allocate
 * Return: a void pointer to the newly allocated memory block.
 */
void *sh_realloc(void *p, size_t size)
{
	if (size == 0)
	{
		free(p);
		return (NULL);
	}
	else if (p == NULL)
	{
		return (malloc(size));
	}
	else
	{
		void *new_p = malloc(size);

		if (new_p == NULL)
		{
			return (NULL);
		}
		sh_memcpy(new_p, p, size);
		free(p);
		return (new_p);
	}
}

/**
 * shell_env -  prints environment variable
 * takes no arguments
 * Return: 0 on success
 */
int shell_env(void)
{
	int m = 0;

	while ((environ[m]))
	{
		sh_printer(environ[m]);
		sh_printer("\n");
		m++;
	}

	return (0);
}
