#include "main.h"
/**
 * free_list - free env list
 * @list: linked list
 * Return: nothing
 */

void free_list(list_t *list)
{
	list_t *temp1, *temp2;

	if (!list)
		return;
	temp1 = list;
	temp2 = list->next;
	while (temp1 && temp2)
	{
		free(temp1->str);
		free(temp1);
		temp1 = temp2;
		temp2 = temp1->next;
	}
	if (temp1)
	{
		free(temp1->str);
		free(temp1);
	}

}
/**
 * free_info - free info struct
 * @info: info struct
 * @n: free case
 * Return: void
 */
void free_info(info_t *info, int n)
{
	int i;

	if (n == 1)
	{
		free_list(info->env);
		free(info->arg);
	}
	for (i = 0; info->argv && info->argv[i]; i++)
		free(info->argv[i]);
	if (info->argv)
		free(info->argv);
}
/**
 * clear_info - clears info at beginning of loop
 * @info: info struct
 * Return: void
 */
void clear_info(info_t *info)
{
	info->argc = 0;
	info->arg = NULL;
	info->argv = NULL;
	info->linecnt++;
}
