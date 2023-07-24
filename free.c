#include "main.h"
/**
 * free_list - free env list
 * @list: linked list
 * Return: nothing
 */

void free_list(list_t *list)
{
	list_t *temp1, *temp2;

	temp1 = list;
	temp2 = list->next;
	while (temp1 && temp2)
	{
		free(temp1->str);
		free(temp1);
		temp1 = temp2;
		temp2 = temp1->next;
	}
	free(temp1);

}
void free_info(info_t *info, int n)
{
	int i;

	if (n == 1)
	{
		free_list(info->env);
		free(info->path);
	}
	for (i = 0; info->argv[i]; i++)
		free(info->argv[i]);
	free(info->argv);
	free(info->arg);
}
void clear_info(info_t *info)
{
	info->argc = 0;
	info->linecnt++;
}
