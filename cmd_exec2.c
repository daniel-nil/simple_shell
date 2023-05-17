#include "main.h"

/**
 * sh_semicolon - handles ";" separator
 * @input: input string that needs to be tokenized
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
 * sh_del_token - breaks a string into tokens using strtok() function
 * @input: input string that needs to be tokenized.
 * @tok: array that will hold the resulting tokens
 * @maxitok: max no of tokens that can be extracted from the input string
 * @del: delimiter string
 * Return: number of tokens
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
