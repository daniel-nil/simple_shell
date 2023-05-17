#include "main.h"

/**
 * sh_exit - skips builtin
 * @tok: tokenizer
 */
void sh_exit(char **tok)
{
	int size = 0;
	const char *err_msg;

	while (tok[size] != NULL)
	{
		size++;
	}
	if (size > 2)
	{
		err_msg = "Error: too many arguments\n";
		write(STDERR_FILENO, err_msg, sh_strlen(err_msg));
	}
	else if (size == 2)
	{
		exit(atoi(tok[1]));
	}
	else
	{
		exit(0);
	}
}

/**
 * sh_env - the builtin
 * @env: environment
 */
void sh_env(char **env)
{
	while (*env != NULL)
	{
		size_t len;

		len = sh_strlen(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * sh_cdexec - cd builter
 * @tok: tokenizer
 * Return: 0
 */
int sh_cdexec(char **tok)
{
	char *f_new = getcwd(NULL, 0);
	char *f_prev = getenv("OLDPWD");

	if (tok[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
		}
	}
	else if (sh_strcmp(tok[1], "-") == 0)
	{
		if (f_prev == NULL)
			perror("cd: OLDPWD not set\n");
		else
		{
			if (chdir(f_prev) != 0)
			{
				perror("cd");
			}
			write(STDERR_FILENO, f_prev, sh_strlen(f_prev));
			write(STDERR_FILENO, "\n", 1);
		}
	}
	else
	{
		if (chdir(tok[1]) != 0)
		{
			perror("cd");
		}
	}
	if (f_new == NULL)
	{
		perror("getcwd failed");
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", f_new, 1);
	free(f_new);
	return (1);
}

/**
 * sh_setenv - setenv
 * @args: tokenizer commands
 * Return: 0 or 1
 */
void sh_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "setenv: invalid arguments\n",
		sh_strlen("setenv: invalid arguments\n"));
	}
	else
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			write(STDERR_FILENO, "setenv: failed to set variable\n",
			sh_strlen("setenv: failed to set variable\n"));
		}
	}
}

/**
 * sh_unsetenv - builtin unsetter
 * @args: tokenizer
 * Return: 0 or 1
 */
void sh_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: invalid arguments\n",
		sh_strlen("unsetenv: invalid arguments\n"));
	}
	else
	{
		if (unsetenv(args[1]) != 0)
		{
			write(STDERR_FILENO, "unsetenv: failed to unset variable\n",
			sh_strlen("unsetenv: failed to unset variable\n"));
		}
	}
}
