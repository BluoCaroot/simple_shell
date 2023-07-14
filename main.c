include "main.h"


char **create_argv(char *str);
int main()
{
	char *buff, *argv[];
	size_t n,r;
	int i, j, c, k;

	n = 0, c = 0;
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

		free(argv);
	}
}


char **create_argv(char *str)
{
	int i, n, l;
	char **argv;
	char *token;

	n = 0, l = 0;
	for (i = 0; str[i]; ++i)
		n++;

	for (i = 0; i < n; ++i)
	{
		if (str[i] && str[i] != ' ')
			l++;
	}

	argv = malloc((l + 1) * sizeof(char *));
	token = strtok(str, " ");
	for (int i = 0; i < l; i++)
	{
		argv[i] = (char *) malloc(sizeof(char) * (_strlen(token) + 1));
		strcpy(argv[i], token);
		token = strtok(NULL, " ");
	}
	argv[l] = '\0';
	return (argv);
}


