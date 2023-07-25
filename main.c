#include "main.h"
void create_argv(info_t *info);
void hsh(info_t *t);
void not_found(info_t *info);
char *to_string(int n);
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
	info->program = argv[0];
	
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
	int i;

	r = 0, n = 0, builtin = 0;

	while (r != -1)
	{
		clear_info(info);
		if (interactive(info))
			write(1, "$ ", 2);
		r = getline(&info->arg, &n, stdin);
		for (i = 0; info->arg[i]; ++i)
		{
			if (info->arg[i] == '\n')
				info->arg[i] = '\0';
		}
		if (r != -1)
		{
			create_argv(info);
			builtin = isbuilt_in(info);
			if (!builtin)
				if (!find_cmd(info))
					not_found(info);
		}
		else if (interactive(info))
			write(1, "\n", 1);
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
	int i, l;
	char **argv;
	char *token;

	l = 0;
	for (i = 0; info->arg[i]; ++i)
	{
		if (info->arg[i] == ' ')
			l++;
	}
	argv = malloc((l + 2) * sizeof(char *));
	if (!argv)
		return;
	token = strtok(info->arg, " ");
	for (i = 0; i <= l; ++i)
	{
		argv[i] = (char *) malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(argv[i], token);
		token = strtok(NULL, " ");
	}
	argv[l + 1] = NULL;
	info->argv = argv;
}
void not_found(info_t *info)
{
	char *cnt = to_string(info->linecnt);

	eputs(info->program);
	eputs(": ");
	eputs(cnt);
	eputs(": Can't open ");
	eputs(info->argv[0]);
	eputchar('\n');
	eputchar(BUF_FLUSH);
	free(cnt);
	return;
}
char *to_string(int n)
{
	char *s;
	int cnt = 0, temp;

	temp = n;
	while (temp)
	{
		temp /= 10;
		cnt++;
	}
	s = malloc(cnt + 1);
	s[cnt] = 0;
	while (n)
	{
		s[--cnt] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
