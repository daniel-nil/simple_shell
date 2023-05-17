#include "main.h"
/**
 * main - Entry point og the program
 * @ac: argc
 * @av: argv
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *input = NULL;
	char *tok[MAXITOKEN];
	int num_tok;

	if (ac > 1 && sh_strcmp(av[0], "./hsh") == 0)
	{
		sh_writer(ac, av);
		exit(0);
	}
	while (1)
	{
		if (isatty(0))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		input = sh_reader();
		if (input == NULL)
		{
			if (isatty(0))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			free(input);
			exit(0);
		}
		if (strchr(input, ';') != NULL)
			sh_semicolon(input);
		else
		{
			num_tok = tokenize(input, tok, MAXITOKEN);
			if (num_tok > 0 && strcmp(tok[0], "alias") != 0)
				execute(tok);
		}
		free(input);
	}
	return (0);
}

/**
 * tokenize - breaks a string into tokens using strtok() function
 * @input: input string that needs to be tokenized.
 * @tok: array that will hold the resulting tokens
 * @maxitok: max no of tokens that can be extracted from the input string
 * Return: number of tokens
 */
int tokenize(char *input, char **tok, int maxitok)
{
	int num_tok = 0;
	char *x = strtok(input, " \n");

	while (x != NULL && num_tok < maxitok)
	{
		if (x[0] == '#')
		{
			break;
		}
		tok[num_tok] = x;
		num_tok++;
		x = strtok(NULL, " \n");
	}
	tok[num_tok] = NULL;
	return (num_tok);
}

/**
 * sh_checkercmd - checks if the command is a built in or located in PATH
 * @tok: a pointer to the commands
 * Return: path of the command
 */
char *sh_checkercmd(char **tok)
{
	char *p;
	L_LIST *pat;
	char *builtins[6] = {"exit", "env", "cd", "unsetenv", "setenv", NULL};
	int x;

	for (x = 0; builtins[x]; x++)
	{
		if (sh_strcmp(tok[0], builtins[x]) == 0)
		{
			sh_exec_builtin(tok, environ);
			return (NULL);
		}
	}
	if (access(tok[0], X_OK) == 0)
	{
		p = tok[0];
		return (p);
	}
	else if (access(tok[0], X_OK) != 0)
	{
		pat = the_path();
		p = sh_finder(tok[0], pat);

		if (p == NULL)
		{
			perror(sh_strcat(tok[0], ": command not found\n"));
		}
		else
		{
			return (p);
		}
	}
	return (NULL);
}

/**
 * execute - creates a child process using fork() and executes command
 * @tok: commands executed
 */
void execute(char **tok)
{
	pid_t pid;
	int status;
	char *p = sh_checkercmd(tok);

	if (p == NULL)
	{
		return;
	}
	else if (strcmp(p, "error") == 0)
	{
		write(STDERR_FILENO, "Invalid command\n", strlen("Invalid command\n"));
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(p, tok, environ) == -1)
		{
			perror("execve failure");
			exit(1);
		}
	}
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			
			exit(1);
		}

	}
	else
	{
		perror("fork failed");
		exit(1);
	}
}
