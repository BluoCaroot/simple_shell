#include "main.h"


char **create_argv(char *str);
int main()
{
	char *buff, **argv;
	ssize_t r;
	size_t n;
	int val;
	pid_t pid;
	
	n = 0;
	while(1)
	{
		write(1, "$ ", 2);
		r = getline(&buff, &n, 0);
		if (r == -1)
		{
			write(1, "\n", 1);
			break;
		}
		argv = create_argv(buff);
		pid = fork();
		if (pid == -1)
			perror("Error");
		else if (pid == 0)
		{
			val = execve(argv[0], argv, NULL);
			if (val == -1)
			perror("Error");
		}
		else
			wait(NULL);
		free(argv);
	}
	return (0);
}


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
		_strcpy(argv[i], token);
		token = strtok(NULL, " ");
	}
	argv[l + 1] = NULL;
	return (argv);
}
