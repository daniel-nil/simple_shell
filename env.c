#include "main.h"
/**
 * sh_cus_setenv - duplicate of setenv
 * @varname: variable name
 * @val: new variable
 * @e: checks for var existance
 * Return: 0 or -1
 */
int sh_cus_setenv(const char *varname, const char *val, int e)
{
	int x;
	char *estr;

	estr = (char *)malloc(sh_strlen(varname) + sh_strlen(val) + 2);
	if (!estr)
	{
		return (-1);
	}

	sh_strcpy(estr, varname);
	sh_strcat(estr, "=");
	sh_strcat(estr, val);

	if (sh_getenv(varname))
	{
		if (e)
		{
			x = sh_putenv(estr);
		}
		else
		{
			x = 0;
		}
	}
	else
	{
		x = sh_putenv(estr);
	}

	if (e != 0)
	{
		free(estr);
	}

	return (x);
}

/**
 * sh_cus_unsetenv - duplivate of setenv
 * @varname: variable name
 * Return: 0 or -1
 */
int sh_cus_unsetenv(const char *varname)
{
	int i, j, len;
	char **env, **new_env;

	if (!varname || !*varname)
	{
		return (-1);
	}

	env = environ;

	if (!env || !*env)
	{
		return (-1);
	}

	len = sh_strlen(varname);

	new_env = (char **)malloc(sizeof(char *) * (sh_envsize() + 1));
	if (!new_env)
	{
		return (-1);
	}

	for (i = 0, j = 0; env[i]; i++)
	{
		if (sh_strncmp(env[i], varname, len) != 0 || env[i][len] != '=')
		{
			new_env[j++] = env[i];
		}
	}

	new_env[j] = NULL;

	environ = new_env;

	return (0);
}
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
