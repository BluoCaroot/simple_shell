#include "main.h"
void free_info(info_t info, int n = 0)
{
	if (n = 1)
		free(info->env);
		free(info->path);
	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
	free(arg);
	return;
}
