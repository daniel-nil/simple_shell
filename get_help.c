#include "main.h"

/**
 * sh_reader - reads input using getline
 * Return: input
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
 * sh_printer - writes string to stdin
 * @str: string
 */
void sh_printer(char *str)
{
	size_t len = sh_strlen(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * sh_strlen -  gets char in string
 * @str: string
 * Return: string len
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
 * sh_stderror - puts string to stderr
 * @str: message
 */
void sh_stderror(char *str)
{
	size_t len = sh_strlen(str);

	write(STDERR_FILENO, str, len);
}

/**
 * sh_strcmp - duplicate strcmp
 * @s1: string compared
 * @s2: second string compared
 * Return: string
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
