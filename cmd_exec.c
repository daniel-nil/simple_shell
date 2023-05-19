#include "main.h"

/**
 * sh_semicolon - handles ";" sep
 * @input: input string
 */
void sh_semicolon(char *input)
{
	char *cmd[MAXIARGS];
	char *args[MAXIARGS];
	pid_t pid;
	int x, status;

	sh_del_token(input, cmd, MAXITOKEN, ";");


	for (x = 0; cmd[x] != NULL; x++)
	{
		sh_del_token(cmd[x], args, MAXITOKEN, " \t\n");
		if (args[0] != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execute(args);
				exit(0);
			}
			else if (pid < 0)
			{
				perror("fork failed");
				exit(1);
			}
			else
			{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			}
		}
	}
}

/**
 * sh_del_token - splits string into tokens
 * @input: input string
 * @tok: holds the result token
 * @maxitok: maximum no of tokens
 * @del: delimiter
 * Return: no of tokens
 */
int sh_del_token(char *input, char **tok, int maxitok, char *del)
{
	int numtok = 0;
	char *x = strtok(input, del);

	while (x != NULL && numtok < maxitok)
	{
		tok[numtok] = x;
		numtok++;
		x = strtok(NULL, del);
	}
	tok[numtok] = NULL;
	return (numtok);
}

/**
 * sh_writer - opens script in non-intective mode
 * @ac: argument command
 * @av: argument vector
 * Return: null
 */
int sh_writer(int ac, char **av)
{
	char *input = NULL;
	char *tok[MAXITOKEN];
	int num_tok;
	size_t input_size = 0;
	FILE *file;

	if (ac != 2)
	{
		char error_message[] = "Usage: ";

		write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
		write(STDERR_FILENO, av[0], strlen(av[0]));
		write(STDERR_FILENO, " filename\n", 10);
		exit(1);
	}

	file = fopen(av[1], "r");
	if (file == NULL)
	{
		perror("fopen");
		exit(1);
	}

	while (getline(&input, &input_size, file) != -1)
	{
		num_tok = tokenize(input, tok, MAXITOKEN);
		if (num_tok > 0)
		{
			execute(tok);
		}
	}
	free(input);
	fclose(file);
	return (0);
}
