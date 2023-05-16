#include "main.h"

/**
 * sh_reader - reads user input from stdin using getline()
 * Return: Returns input from stdout
 */
char *sh_reader()
{
	char *input = NULL;
	size_t input_size = 0;

	if (getline(&input, &input_size, stdin) == -1)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

/**
 * sh_printer - writes/print string to stdin
 * @str: string written
 */
void sh_printer(char *str)
{
	size_t len = sh_strlen(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * sh_strlen -  gets no. of characters in a string
 * @str: string whose length is calculated
 * Return: Length of string
 */
int sh_strlen(const char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

/**
 * sh_stderror - writes string to stderr
 * @str: Error message printed
 */
void sh_stderror(char *str)
{
	size_t len = sh_strlen(str);

	write(STDERR_FILENO, str, len);
}

/**
 * sh_strcmp - compares two strings and return their difference
 * @str1: the string compared
 * @str2: the second string compared
 * Return: the diff btwn the ASCII values of the characters pointed by str
 */
int sh_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
