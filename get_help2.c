#include "main.h"
/**
 * sh_constr - combines two strings
 * @s1: string concetenated
 * @s2: string to be combined
 * Return: comibination
 */
char *sh_constr(char *s1, char *s2)
{
	int l1 = sh_strlen(s1);
	int l2 = sh_strlen(s2);
	char *r = malloc(l1 + l2 + 1);

	if (r == NULL)
	{
		perror("Failed to allocate memory for concatenated string");
		exit(1);
	}
	r = sh_strcpy(r, s1);
	r = sh_strcat(r, s2);
	return (r);
}

/**
 * sh_strcpy - duplicate strcpy
 * @dest: destination
 * @src: string to be copied
 * Return: src
 */
char *sh_strcpy(char *dest, const char *src)
{
	char *x = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (x);
}

/**
 * sh_strcat - duplicate strcat
 * @dest: destiation
 * @src: string
 * Return: combination
 */
char *sh_strcat(char *dest, const char *src)
{
	char *x = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (x);
}

/**
 * sh_strncmp - duplicate strncmp
 * @s1: string to be compared
 * @s2: string to be compared with
 * @n: comparer
 * Return: 0
 */
int sh_strncmp(const char *s1, const char *s2, size_t x)
{
	size_t z;

	for (z = 0; z < x; z++)
	{
		if (*s1 == '\0' || *s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

/**
 * my_strdup - duplicate strdup
 * @str: string
 * Return: pointer
 */
char *sh_strdup(const char *str)
{
	size_t len = sh_strlen(str) + 1;
	char *new_s = malloc(len);

	if (new_s == NULL)
		return (NULL);
	memcpy(new_s, str, len);
	return (new_s);
}
