#include "main.h"

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
