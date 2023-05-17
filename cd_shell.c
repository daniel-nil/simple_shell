#include "main.h"
/**
 * sh_freelist - linked list freer
 * @head: pointer to list
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
 * the_node - adds new node
 * @ref: double pointer
 * @str: string with new node
 */
void the_node(L_LIST **ref, char *str)
{
	L_LIST *nnode = (L_LIST *)malloc(sizeof(L_LIST));

	nnode->str = str;
	nnode->next = *ref;
	*ref = nnode;
}

/**
 * the_path - path finder
 * Return: head node
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
 * sh_getenv - gets value stored in varname
 * @varname: variable name
 * Return: variable
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

/**
 * sh_finder - checks whether file exists and can be executed
 * @cmd: executed cmd
 * @p_list: list to check cmd
 * Return: path for the cmd
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
