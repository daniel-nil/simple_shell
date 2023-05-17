#include "main.h"
/**
 * main - Entry point og the program
 * @argc: argc
 * @argv: argv
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *input = NULL;
	char *tokens[MAXITOKEN];
	int num_tokens;

	if (argc > 1 && sh_strcmp(argv[0], "./hsh") == 0)
	{
		sh_writer(argc, argv);
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
			num_tokens = tokenize(input, tokens, MAXITOKEN);
			if (num_tokens > 0 && strcmp(tokens[0], "alias") != 0)
				execute(tokens);
		}
		free(input);
	}
	return (0);
}

/**
 * tokenize - breaks a string into tokens using strtok() function
 * @input: input string that needs to be tokenized.
 * @tokens: array that will hold the resulting tokens
 * @max_tokens: max no of tokens that can be extracted from the input string
 * Return: number of tokens
 */
int tokenize(char *input, char **tokens, int max_tokens)
{
	int num_tokens = 0;
	char *token = strtok(input, " \n");

	while (token != NULL && num_tokens < max_tokens)
	{
		if (token[0] == '#')
		{
			break;
		}
		tokens[num_tokens] = token;
		num_tokens++;
		token = strtok(NULL, " \n");
	}
	tokens[num_tokens] = NULL;
	return (num_tokens);
}

/**
 * sh_checkercmd - checks if the command is a built in or located in PATH
 * @tokens: a pointer to the commands
 * Return: path of the command
 */
char *sh_checkercmd(char **tokens)
{
	char *path;
	L_LIST *pathLL;
	char *builtins[6] = {"exit", "env", "cd", "unsetenv", "setenv", NULL};
	int i;

	for (i = 0; builtins[i]; i++)
	{
		if (sh_strcmp(tokens[0], builtins[i]) == 0)
		{
			sh_exec_builtin(tokens, environ);
			return (NULL);
		}
	}
	if (access(tokens[0], X_OK) == 0)
	{
		path = tokens[0];
		return (path);
	}
	else if (access(tokens[0], X_OK) != 0)
	{
		pathLL = the_path();
		path = sh_finder(tokens[0], pathLL);

		if (path == NULL)
		{
			perror(sh_strcat(tokens[0], ": command not found\n"));
		}
		else
		{
			return (path);
		}
	}
	return (NULL);
}

/**
 * execute - creates a child process using fork() and executes command
 * @tokens: commands executed
 */
void execute(char **tokens)
{
	pid_t pid;
	int status;
	char *path = sh_checkercmd(tokens);

	if (path == NULL)
	{
		return;
	}
	else if (strcmp(path, "error") == 0)
	{
		write(STDERR_FILENO, "Invalid command\n", strlen("Invalid command\n"));
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
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
