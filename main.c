#include "main.h"
void create_argv(info_t *info);
void hsh(info_t *t);
/**
 * main - simple shell
 * @argc: number of arrguments
 * @argv: array of arguments
 * Return: 0 if succes 1 if fail
 */
int main(int argc, char **argv)
{
	int fd;
	info_t info[] = {INFO_INIT};
	
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs(argv[0]);
				eputs(": 0: Can't open ");
				eputs(argv[1]);
				eputchar('\n');
				eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}	
		info->fd = fd;
	}
	info->env = create_list();
	info->path = path(info->env);
	hsh(info);
	return (EXIT_SUCCESS);
}
/**
 * hsh - shell loop
 * @info: list
 * Return: void
 */

void hsh(info_t *info)
{
	int r, builtin;
	size_t n;

	r = 0, n = 0, builtin = 0;

	while (r != -1)
	{
		clear_info(info);
		if (interactive(info))
			write(1, "$ ", 2);
		r = getline(&info->arg, &n, stdin);
		if (r != -1)
		{
			create_argv(info);
			builtin = isbuilt_in(info);
			if (!builtin)
				if (!find_cmd(info))
					not_found(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	/* here error status will be checked */


	return;
}

/**
 * create_argv - creates argument array to be passed to execve
 * @str: input string
 * Return: void
 */
void create_argv(info_t *info)
{
	int i, cnt = 0;
	char * temp = strtok(info->arg, " ");
	
	for (i = 0; info->arg[i]; ++i)
		if (info->arg[i] == ' ')
			cnt++;
	info->argv = malloc(sizeof(char *) * (cnt + 2));
	i = 0;
	while (temp)
	{
		info->argv[i] = temp;
		temp = strtok(NULL, " ");
		i++;
	}
	info->argv[i] = NULL;
	info->argc = cnt + 1;
	return;
}
