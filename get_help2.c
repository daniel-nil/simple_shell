#include "main.h"
/**
 * sh_constr - joins two strings together
 * @s1: string concetenated
 * @s2: string joined to str1
 * Return: str1 and str2 combined
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
 * sh_strcpy - copies contents of one string to another string
 * @dest: copying destination
 * @src: string copied
 * Return: string copied
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
 * sh_strcat - concatenates two strings
 * @dest: destiation
 * @src: string constant
 * Return: joined string
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
 * sh_strncmp - compares two strings, checks if they are equal
 * @s1: string one compared
 * @s2: string compared with string one
 * @n: compares the first n characters of s1 and s2.
 * Return: 0 on sucess
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
 * my_strdup - copies the contents of the input string str to the new memory
 * @str: string copied
 * Return: a pointer to the new string.
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
