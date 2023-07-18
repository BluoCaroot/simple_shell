#include "main.h"

char *path(char *argv0, list_t *head)
{
	char *pth;
	list_t *temp;
	temp = head;
	while (temp)
	{
		if (_strncmp(temp->str, "PATH", 4));
			temp = temp->next;
		else
		{

			pth = &(temp->str[5]);
			break;
		}
			
	}
	return (pth);

}

int add_node_end(list_t **node, char *str);

list_t *create_list(void)
{
	int i, temp;
	list_t *head = NULL;

	for (i = 0; environ[i]; ++i)
	{
		temp = add_node_end(head, environ[i]);
		if (temp == -1)
			perror("error");
	}
	return (head);
}


int add_node_end(list_t *head, char *str)
{
	list_t *tail, *temp;

	temp = head;
	tail = malloc(sizeof(list_t));
	if (!tail)
		return (-1);
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
		head = tail;
	return (0);
}
