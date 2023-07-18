#include "main.h"
char **create_argv(char *str);
/**
 * main - simple shell
 * Return: 0 if succes -1 if fail
 */
int main(void)
{
	char *buff = NULL, **argv;
	ssize_t r = 0;
	size_t n = 0;
	int val, i;
	pid_t pid;
	list_t *env;

	env = create_list();

	while (1)
	{
		write(1, "$ ", 2);
		r = getline(&buff, &n, stdin);
		if (r == -1)
		{
			write(1, "\n", 1);
			free(buff);
			return (0);
		}
		for (i = 0; buff[i]; ++i)
		{
			if (buff[i] == '\n')
				buff[i] = '\0';
		}
		argv = create_argv(buff);
		if(!argv)
		{
			write(1, "\n", 1);
			free(buff);
			return(0);
		}
		iscommand(pth);
		if (iscommand())
			pid = fork();
		if (pid == -1)
			perror("Error");
		else if (pid == 0)
		{
			val = execve(argv[0], argv, NULL);
			if (val == -1)
			{
				perror("Error");
				return (-1);
			}
		}
		else
			wait(NULL);
		free(argv);
	}
	return (0);
}

/**
 * create_argv - creates argument array to be passed to execve
 * @str: input string
 * Return: the array to be passed
 */
char **create_argv(char *str)
{
	int i, l;
	char **argv;
	char *token;

	l = 0;
	for (i = 0; str[i]; ++i)
	{
		if (str[i] == ' ')
			l++;
	}

	argv = malloc((l + 2) * sizeof(char *));
	if (!argv)
		return (NULL);
	token = strtok(str, " ");
	for (i = 0; i <= l; i++)
	{
		argv[i] = (char *) malloc(sizeof(char) * (_strlen(token) + 1));
		if (!argv[i])
			return(NULL);
		_strcpy(argv[i], token);
		token = strtok(NULL, " ");
	}
	argv[l + 1] = NULL;
	return (argv);
}
