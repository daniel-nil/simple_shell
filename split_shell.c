#include "main.h"

/**
 * sh_delim - searches delimeter
 * @c: char
 * @del: delimiter
 * Return: 0 or -1
 */
unsigned int sh_delim(char c, char *del)
{
	while (*del != '\0')
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}

/**
 * sh_strtok - duplicate strtok
 * @ssrc: source
 * @del: delimeter
 * Return: 0 or -1
 */
char *sh_strtok(char *ssrc, char *del)
{
	static char *x;
	char *i;

	if (!ssrc)
	{
		ssrc = x;
	}
	if (!ssrc)
	{
		return (NULL);
	}
	while (1)
	{
		if (sh_delim(*ssrc, del))
		{
			ssrc++;
			continue;
		}
		if (*ssrc == '\0')
		{
			return (NULL);
		}
		break;
	}
	i = ssrc;
	while (1)
	{
		if (*ssrc == '\0')
		{
			x = ssrc;
			return (i);
		}
		if (sh_delim(*ssrc, del))
		{
			*ssrc = '\0';
			x = ssrc + 1;
			return (i);
		}
		ssrc++;
	}
}
