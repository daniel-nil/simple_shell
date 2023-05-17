#include "main.h"

/**
 * sh_cus_setenv - clone of setenv
 * @varname: variable name
 * @val: new variable value
 * @e: checks if variable exists or not
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
 * sh_cus_unsetenv - clone of setenv
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
