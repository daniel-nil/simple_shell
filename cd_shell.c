#include "main.h"
/**
 * sh_freelist - frees linked list
 * @head: a pointer to the head node of the list
 */
void sh_freelist(L_LIST *head)
{
	L_LIST *temp;

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
 * @ref: a double pointer to the head node
 * @str: string stored on the new node
 */
void the_node(L_LIST **ref, char *str)
{
	L_LIST *nnode = (L_LIST *)malloc(sizeof(L_LIST));

	nnode->str = str;
	nnode->next = *ref;
	*ref = nnode;
}
/**
 * the_path - finds the path in env variable
 * Return: head node to the linked list
 */
L_LIST *the_path(void)
{
	L_LIST *head = NULL;
	char *p = getenv("PATH");
	char *x = sh_strdup(p);
	L_LIST *node;
	char *token;

	if (!x)
	{
		perror("malloc failure");
		return (NULL);
	}
	token = strtok(x, ":");

	while (token != NULL)
	{
		node = malloc(sizeof(L_LIST));
		if (!node)
		{
			perror("malloc failure");
			sh_freelist(head);
			free(x);
			return (NULL);
		}

		node->str = sh_strdup(token);
		node->next = head;
		head = node;

		token = strtok(NULL, ":");
	}
	free(x);

	return (head);
}
/**
 * sh_finder - checks if the file exists and is executable
 * @cmd: command being executed
 * @p_list: list of directories to check command
 * Return: executable path for the command
 */
char *sh_finder(char *cmd, L_LIST *p_list)
{
	char *execpath = NULL;
	char *p = NULL;
	int cmd_len = sh_strlen(cmd);
	int p_len;
	int new_len;
	char *new_p;

	while (p_list != NULL)
	{
		p = p_list->str;
		p_len = sh_strlen(p);
		new_len = p_len + cmd_len + 2;
		new_p = malloc(new_len * sizeof(char));
		if (new_p == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		sh_strcpy(new_p, p);
		sh_strcat(new_p, "/");
		sh_strcat(new_p, cmd);
		if (access(new_p, X_OK) == 0)
		{
			execpath = new_p;
		break;
		}
		free(new_p);
		p_list = p_list->next;
	}
	return (execpath);
}
/**
 * sh_getenv - gets the value stored in specified variable name
 * @varname: Variable name
 * Return: values stored in the variable
 */
char *sh_getenv(const char *varname)
{
	int x, len;
	char *envval;

	len = sh_strlen(varname);

	for (x = 0; environ[x] != NULL; x++)
	{
		if (sh_strncmp(varname, environ[x], len) == 0 && environ[x][len] == '=')

		{
			envval = &environ[x][len + 1];

			return (envval);
		}
	}

	return (NULL);
}
