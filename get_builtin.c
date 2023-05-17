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
