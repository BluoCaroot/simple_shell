#include "main.h"
/**
 * free_list - free env list
 * @list: linked list
 * Return: nothing
 */

void free_list(list_t *list)
{
	list_t *temp1, *temp2;

	temp1 = env;
	temp2 = env->next;
	while (temp1 && temp2)
	{
		free(temp1);
		free(temp2);
		temp1 = temp2;
		temp2 = temp2->next;
	}
	free(temp1);

}
void free_info(info_t *info, int n)
{
	if (n == 1)
	{
		free_list(info->env);
		free(info->path);
	}
	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
	free(arg);
}
