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
