#include "main.h"

/**
 * sh_exec_builtin - handles builtin functions
 * @tokens: tokenized commands
 * @env: contains values of environ
 */
void sh_exec_builtin(char **tokens, char **env)
{
	if (sh_strcmp(tokens[0], "exit") == 0)
	{
		sh_exit(tokens);
	}
	else if (sh_strcmp(tokens[0], "env") == 0)
	{
		sh_env(env);
	}

	else if (sh_strcmp(tokens[0], "cd") == 0)
	{
		sh_cdexec(tokens);
	}

	else if (sh_strcmp(tokens[0], "setenv") == 0)
	{
		sh_setenv(tokens);
	}
	else if (sh_strcmp(tokens[0], "unsetenv") == 0)
	{
		sh_unsetenv(tokens);
	}
}
