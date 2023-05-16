#include "main.h"

/**
 * sh_cus_setenv - clone of setenv
 * @name: variable name
 * @value: new variable value
 * @overwrite: checks if variable exists or not
 * Return: 0 or -1
 */
int sh_cus_setenv(const char *name, const char *value, int overwrite)
{
	int result;
	char *envstr;

	envstr = (char *)malloc(sh_strlen(name) + sh_strlen(value) + 2);
	if (!envstr)
	{
		return (-1);
	}

	sh_strcpy(envstr, name);
	sh_strcat(envstr, "=");
	sh_strcat(envstr, value);

	if (sh_getenv(name))
	{
		if (overwrite)
		{
			result = sh_putenv(envstr);
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		result = sh_putenv(envstr);
	}

	if (result != 0)
	{
		free(envstr);
	}

	return (result);
}

/**
 * sh_cus_unsetenv - clone of setenv
 * @name: variable name
 * Return: 0 or -1
 */
int sh_cus_unsetenv(const char *name)
{
	int i, j, len;
	char **envp, **newenvp;

	if (!name || !*name)
	{
		return (-1);
	}

	envp = environ;

	if (!envp || !*envp)
	{
		return (-1);
	}

	len = sh_strlen(name);

	newenvp = (char **)malloc(sizeof(char *) * (sh_envsize() + 1));
	if (!newenvp)
	{
		return (-1);
	}

	for (i = 0, j = 0; envp[i]; i++)
	{
		if (sh_strncmp(envp[i], name, len) != 0 || envp[i][len] != '=')
		{
			newenvp[j++] = envp[i];
		}
	}

	newenvp[j] = NULL;

	environ = newenvp;

	return (0);
}
