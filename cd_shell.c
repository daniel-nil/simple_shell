#include "main.h"
/**
 * sh_freelist - frees linked list
 * @head: a pointer to the head node of the list
 */
void sh_freelist(LL *head)
{
	LL *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}
/**
 * the_node - adds a new node to the list
 * @head_ref: a double pointer to the head node
 * @str: string stored on the new node
 */
void the_node(LL **head_ref, char *str)
{
	LL *new_node = (LL *)malloc(sizeof(LL));

	new_node->str = str;
	new_node->next = *head_ref;
	*head_ref = new_node;
}
/**
 * the_path - finds the path in env variable
 * Return: head node to the linked list
 */
LL *the_path(void)
{
	LL *head = NULL;
	char *path = getenv("PATH");
	char *path_copy = sh_strdup(path);
	LL *node;
	char *token;

	if (!path_copy)
	{
		perror("malloc failure");
		return (NULL);
	}
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		node = malloc(sizeof(LL));
		if (!node)
		{
			perror("malloc failure");
			sh_freelist(head);
			free(path_copy);
			return (NULL);
		}

		node->str = sh_strdup(token);
		node->next = head;
		head = node;

		token = strtok(NULL, ":");
	}
	free(path_copy);

	return (head);
}
/**
 * sh_finder - checks if the file exists and is executable
 * @command: command being executed
 * @path_list: list of directories to check command
 * Return: executable path for the command
 */
char *sh_finder(char *command, LL *path_list)
{
	char *executable_path = NULL;
	char *path = NULL;
	int command_len = sh_strlen(command);
	int path_len;
	int new_len;
	char *new_path;

	while (path_list != NULL)
	{
		path = path_list->str;
		path_len = sh_strlen(path);
		new_len = path_len + command_len + 2;
		new_path = malloc(new_len * sizeof(char));
		if (new_path == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		sh_strcpy(new_path, path);
		sh_strcat(new_path, "/");
		sh_strcat(new_path, command);
		if (access(new_path, X_OK) == 0)
		{
			executable_path = new_path;
		break;
		}
		free(new_path);
		path_list = path_list->next;
	}
	return (executable_path);
}
/**
 * sh_getenv - gets the value stored in specified variable name
 * @name: Variable name
 * Return: values stored in the variable
 */
char *sh_getenv(const char *name)
{
	int i, len;
	char *env_val;

	len = sh_strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (sh_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')

		{
			env_val = &environ[i][len + 1];

			return (env_val);
		}
	}

	return (NULL);
}
