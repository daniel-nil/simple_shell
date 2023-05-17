#include "main.h"

/**
 * sh_memcpy - duplicate memcpy
 * @dest: destination buffer
 * @src: source buffer
 * @x: bytes to copy
 * Return: void
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
 * sh_realloc - duplicate realloc
 * @p: pointer
 * @size: new size
 * Return: void
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
 * shell_env -  environment printer
 * Return: 0
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
