#include "main.h"

/**
 * sh_reader - reads user input from stdin using getline()
 * Return: Returns input from stdout
 */
char *sh_reader()
{
	char *input = NULL;
	size_t size = 0;

	if (getline(&input, &size, stdin) == -1)
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
	int l = 0;

	while (*str != '\0')
	{
		l++;
		str++;
	}
	return (l);
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
 * @s1: the string compared
 * @s2: the second string compared
 * Return: the diff btwn the ASCII values of the characters pointed by str
 */
int sh_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
