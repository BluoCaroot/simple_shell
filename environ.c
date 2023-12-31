#include "main.h"
/**
 * path - gets path variable
 * @head: head of env list
 * Return: path
 */
char *path(list_t *head)
{
	list_t *temp;

	temp = head;
	while (temp)
	{
		if (_strncmp(temp->str, "PATH=", 5))
			temp = temp->next;
		else if (temp->str[5])
			return (&(temp->str[5]));
	}
	return (NULL);

}

int add_node_end(list_t **node, char *str);
/**
 * create_list - creates list
 * Return: env list
 */
list_t *create_list(void)
{
	int i, temp;
	list_t *head = NULL;

	if (!environ)
		return (NULL);

	for (i = 0; environ[i]; ++i)
	{
		temp = add_node_end(&head, environ[i]);
		if (temp == -1)
			perror("error");
	}
	return (head);
}

/**
 * add_node_end - adds node to list end
 * @head: head of list
 * @str: string to add
 * Return: 0 if success -1 if fail
 */
int add_node_end(list_t **head, char *str)
{
	list_t *tail, *temp;

	temp = *head;
	tail = malloc(sizeof(list_t));
	if (!tail)
		return (-1);
	_memset((void *)tail, 0, sizeof(list_t));
	if (str)
	{
		tail->str = _strdup(str);
		if (!tail->str)
		{
			free(tail);
			return (-1);
		}
	}
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = tail;
	}
	else
		*head = tail;
	return (0);
}
/**
 * interactive - checks if current STDIN is a terminal
 * @info: info struct
 * Return: 1 or 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->fd <= 2);
}
/**
 * list_to_str - converts linked list to array of strings
 * @head: env list
 * Return: env strings
 */
char **list_to_str(list_t *head)
{
	list_t *node = head;
	int i = 0, j;
	char **ans, *temp;

	if (!head)
		return (NULL);
	while (node)
	{
		i++;
		node = node->next;
	}
	if (!i)
		return (NULL);
	ans = malloc(sizeof(char *) * (i + 1));
	if (!ans)
		return (NULL);
	for (i = 0, node = head; node; node = node->next, ++i)
	{
		temp = malloc(_strlen(node->str) + 1);
		if (!temp)
		{
			for (j = 0; j < i; ++j)
				free(ans[j]);
			free(ans);
			return (NULL);
		}
		temp = _strcpy(temp, node->str);
		ans[i] = temp;
	}
	ans[i] = NULL;
	return (ans);
}
