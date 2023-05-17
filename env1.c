#include "main.h"

/**
 * sh_putenv - duplicate putenv
 * @str: string
 * Return: 1 or 0
 */
int sh_putenv(char *str)
{
	int x = 0;
	char **new_env = NULL;
	int a, b;

	if (!str || !*str || strchr(str, '=') == NULL)
	{
		return (-1);
	}

	new_env = (char **)malloc(sizeof(char *) * (sh_envsize() + 2));
	if (!new_env)
	{
		return (-1);
	}

	for (a = 0, b = 0; environ[a] != NULL; a++)
	{
		if (sh_strncmp(environ[a], str, sh_strchr(str, '=') - str) != 0)
		{
			new_env[b++] = environ[a];
		}
		else
		{
			x = 1;
		}
	}

	new_env[b++] = str;

	new_env[b] = NULL;

	environ = new_env;

	return (x);
}

/**
 * sh_strchr - duplicate strchr
 * @str: string
 * @z: char
 * Return: 0 or first occurence z
 */
char *sh_strchr(const char *str, int z)
{
	while (*str)
	{
		if (*str == z)
		{
		return ((char *)str);
		}
		str++;
	}
	if (*str == z)
	{
		return ((char *)str);
	}
	return (NULL);
}

/**
 * sh_envsize - duplicate environSize
 * Return: size of e variable
 */
int sh_envsize(void)
{
	int x = 0;
	char **e = environ;

	while (*e != NULL)
	{
		x++;
		e++;
	}
	return (x);
}
