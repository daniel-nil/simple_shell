#include "main.h"
/**
 * sh_exec_builtin - builtin function executor
 * @tok: tokenizer
 * @env: environ
 */
void sh_exec_builtin(char **tok, char **env)
{
	if (sh_strcmp(tok[0], "exit") == 0)
	{
		sh_exit(tok);
	}
	else if (sh_strcmp(tok[0], "env") == 0)
	{
		sh_env(env);
	}

	else if (sh_strcmp(tok[0], "cd") == 0)
	{
		sh_cdexec(tok);
	}

	else if (sh_strcmp(tok[0], "setenv") == 0)
	{
		sh_setenv(tok);
	}
	else if (sh_strcmp(tok[0], "unsetenv") == 0)
	{
		sh_unsetenv(tok);
	}
}

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
