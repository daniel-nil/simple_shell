#include "shell.h"

/**
 * execute_builtins - handles builtin functions
 * @tokens: tokenized commands
 * @env: contains values of environ
 */
void execute_builtins(char **tokens, char **env)
{
	if (my_strcmp(tokens[0], "exit") == 0)
	{
		execute_exit(tokens);
	}
	else if (my_strcmp(tokens[0], "env") == 0)
	{
		execute_env(env);
	}

	else if (my_strcmp(tokens[0], "cd") == 0)
	{
		execute_cd(tokens);
	}

	else if (my_strcmp(tokens[0], "setenv") == 0)
	{
		shell_setenv(tokens);
	}
	else if (my_strcmp(tokens[0], "unsetenv") == 0)
	{
		shell_unsetenv(tokens);
	}
}
